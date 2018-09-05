#include "PipeLineUtility.h"
#include "..\Framework\RenderDevice.h"
#include "..\Mathematics\Matrix.h"
#include "..\Framework\Camera.h"
#include "..\Mathematics\MathUtil.h"
#include "..\Mathematics\Float4.h"
#include <tuple>
#include <functional>
using namespace std;

Matrix RenderPipeLine::m_ViewPortMatrix;

void RenderPipeLine::DrawLine(float startX, float startY, float endX, float endY, DWORD color, DrawLineType type)
{
	switch (type)
	{
	case DDA:
	{
		float dx = endX - startX;
		float dy = endY - startY;

		float steps = std::max<float>(std::abs(dx), std::abs(dy));

		float increx = dx / steps;
		float increy = dy / steps;

		float xi = startX;
		float yi = startY;

		for (int i = 0; i < steps; i++)
		{
			RenderDevice::getSingletonPtr()->DrawPixel(std::lround(xi), std::lround(yi), color);

			xi += increx;
			yi += increy;
		}
	}
	break;
	case Bresenham:
	{
		int dx = static_cast<int>(endX - startX);
		int dy = static_cast<int>(endY - startY);

		int ux = (dx > 0) ? 1 : -1;
		int uy = (dy > 0) ? 1 : -1;

		int xi = static_cast<int>(startX);
		int yi = static_cast<int>(startY);

		int eps = 0;
		dx = std::abs(dx);
		dy = std::abs(dy);

		if (dx > dy)
		{
			for (; xi != std::round(endX); xi += ux)
			{
				RenderDevice::getSingletonPtr()->DrawPixel(xi, yi, color);
				eps += dy;
				if ((eps << 1) >= dx)
				{
					yi += uy;
					eps -= dx;
				}
			}
		}
		else
		{
			for (; yi != std::round(endY); yi += uy)
			{
				RenderDevice::getSingletonPtr()->DrawPixel(xi, yi, color);
				eps += dx;
				if ((eps << 1) >= dy)
				{
					xi += ux;
					eps -= dy;
				}
			}
		}
	}
	break;
	default:
		break;
	}
	
}

void RenderPipeLine::DrawCall(Matrix viewMat, Matrix projMat, vector<float3> vertices, vector<int> indices)
{
	auto vp = viewMat * projMat;

	auto indexLength = indices.size();
	for (int index = 0; index < indexLength; index +=3 )
	{
		auto index0 = indices[index + 0];
		auto index1 = indices[index + 1];
		auto index2 = indices[index + 2];

		auto v0 = float4(vertices[index0], 1.0f);
		auto v1 = float4(vertices[index1], 1.0f);
		auto v2 = float4(vertices[index2], 1.0f);

		v0 = v0 * vp;
		v1 = v1 * vp;
		v2 = v2 * vp;

		v0 = MathUtil::Homogenous(v0);
		v1 = MathUtil::Homogenous(v1);
		v2 = MathUtil::Homogenous(v2);

		v0 = v0 * m_ViewPortMatrix;
		v1 = v1 * m_ViewPortMatrix;
		v2 = v2 * m_ViewPortMatrix;

		RasterizeBarycentric(tuple<float4>(v0), tuple<float4>(v1), tuple<float4>(v2));
		//Rasterize(tuple<float4>(v0), tuple<float4>(v1), tuple<float4>(v2));

// 		DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;
// 		DrawLine(v0.x, v0.y, v1.x, v1.y, color, DrawLineType::DDA);
// 		DrawLine(v0.x, v0.y, v2.x, v2.y, color, DrawLineType::DDA);
// 		DrawLine(v1.x, v1.y, v2.x, v2.y, color, DrawLineType::DDA);
	}
}

vector<tuple<float4>> RenderPipeLine::SplitTriangle(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2)
{
	vector<tuple<float4>> vertices;

	auto v3 = v0;
	auto v4 = v1;
	auto v5 = v2;

	float4 position0 = get<0>(v0);
	float4 position1 = get<0>(v1);
	float4 position2 = get<0>(v2);

	float dy1_0 = position1.y - position0.y;
	float dy2_0 = position2.y - position0.y;
	float dx2_0 = position2.x - position0.x;
	float dz1_0 = position1.z - position0.z;
	float dz2_0 = position2.z - position0.z;

	// dx(new-0)/dx(2-0) = dy(1-0)/dy(2-0) => newX = 0 + dy(1-0)/dy(2-0)*dx(2-0)
	float newX = position0.x + (dy1_0 / dy2_0)*dx2_0;
	float newZ = position0.z + (dy1_0 / dy2_0)*dz2_0;

	//////////////////////////////////////////////////////////////////////////
	// v0, v1, v2
	vertices.push_back({ position0 });
	vertices.push_back({ position1 });
	vertices.push_back({ float4(newX, position1.y, newZ, 1) });

	//////////////////////////////////////////////////////////////////////////
	// v3, v4, v5
	vertices.push_back({ position1 });
	vertices.push_back({ position2 });
	vertices.push_back({ float4(newX, position1.y, newZ, 1) });

	return vertices;
}

void RenderPipeLine::Rasterize(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2)
{
	auto position0 = ref(get<0>(v0));
	auto position1 = ref(get<0>(v1));
	auto position2 = ref(get<0>(v2));

	// 在 y 轴上 进行排序 使 v0 <= v1 < = v2
	if (position1.get().y < position0.get().y)
	{
		std::swap(v1, v0);
	}

	if (position2.get().y < position0.get().y)
	{
		std::swap(v2, v0);
	}

	if (position2.get().y < position1.get().y)
	{
		std::swap(v2, v1);
	}

	// y0 == y1 则是平底三角形
	if (MathUtil::IsEqual(position0.get().y, position1.get().y))
	{
		std::swap(v2, v0);

		if (position2.get().x < position1.get().x)
		{
			std::swap(v2, v1);
		}

		// 光栅化三角形
		RasterizeFace(position0, position1, position2);
	}

	// y1 == y2 则是平顶三角形
	else if (MathUtil::IsEqual(position1.get().y, position2.get().y))
	{
		if (position2.get().x < position1.get().x)
		{
			std::swap(v2, v1);
		}

		// 光栅化三角形
		RasterizeFace(position0, position1, position2);
	}

	// 任意三角形
	else
	{
		// 分裂三角形
		auto vertices = SplitTriangle(v0, v1, v2);

		for (int i=0;i<vertices.size();i+=3)
		{
			// 光栅化三角形
			Rasterize(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
		}
	}
}

void RenderPipeLine::RasterizeBarycentric(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2)
{
	float x0 = get<0>(v0).x;
	float y0 = get<0>(v0).y;

	float x1 = get<0>(v1).x;
	float y1 = get<0>(v1).y;

	float x2 = get<0>(v2).x;
	float y2 = get<0>(v2).y;

	// 计算斜率
	//f01（x，y） = （y0 - y1） * x + （x1 - x0） * y + x0 * y1 - x1 * y0
	//f12（x，y） = （y1 - y2） * x + （x2 - x1） * y + x1 * y2 - x2 * y1
	//f20（x，y） = （y2 - y0） * x + （x0 - x2） * y + x2 * y0 - x0 * y2

	auto slope0 = (y0 - y1) * x2 + (x1 - x0) * y2 + x0 * y1 - x1 * y0;
	auto slope1 = (y1 - y2) * x0 + (x2 - x1) * y0 + x1 * y2 - x2 * y1;
	auto slope2 = (y2 - y0) * x1 + (x0 - x2) * y1 + x2 * y0 - x0 * y2;

	// 不绘制计算结果斜率为0的三角形
	if (MathUtil::IsEqual(abs(slope0), 0.0f) || MathUtil::IsEqual(abs(slope1), 0.0f) || MathUtil::IsEqual(abs(slope2), 0.0f))
	{
		return;
	}

	auto invSlope0 = 1.0f / slope0;
	auto invSlope1 = 1.0f / slope1;
	auto invSlope2 = 1.0f / slope2;

	int xMin = lround((x0 < x1 ? x0 : x1) < x2 ? (x0 < x1 ? x0 : x1) : x2);
	int xMax = lround((x0 > x1 ? x0 : x1) > x2 ? (x0 > x1 ? x0 : x1) : x2);
	int yMin = lround((y0 < y1 ? y0 : y1) < y2 ? (y0 < y1 ? y0 : y1) : y2);
	int yMax = lround((y0 > y1 ? y0 : y1) > y2 ? (y0 > y1 ? y0 : y1) : y2);

	DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	for (int x = xMin; x <= xMax; ++x)
	{
		for (int y = yMin; y <= yMax; ++y)
		{
			float a = 1.0f / 3.0f;
			float b = 1.0f / 3.0f;
			float c = 1.0f / 3.0f;

			if (CalcWeight(x, y, a, b, c, v0, v1, v2, invSlope0, invSlope1, invSlope2))
			{
				// 绘制像素点
				RenderDevice::getSingletonPtr()->DrawPixel(std::lround(x), std::lround(y), color);
			}
		}
	}
}

bool RenderPipeLine::CalcWeight(
	float x, float y,
	float& a, float& b, float& c, 
	tuple<float4> v0, tuple<float4> v1, tuple<float4> v2,
	float slope0, float slope1, float slope2)
{
	float x0 = get<0>(v0).x;
	float y0 = get<0>(v0).y;

	float x1 = get<0>(v1).x;
	float y1 = get<0>(v1).y;

	float x2 = get<0>(v2).x;
	float y2 = get<0>(v2).y;

	// 计算权重
	a = ((y1 - y2) * x + (x2 - x1) * y + x1 * y2 - x2 * y1) * slope1;
	b = ((y2 - y0) * x + (x0 - x2) * y + x2 * y0 - x0 * y2) * slope2;
	c = ((y0 - y1) * x + (x1 - x0) * y + x0 * y1 - x1 * y0) * slope0;

	// 判断是否在三角形内
	return a >= 0.0f && a >= 0.0f &&a >= 0.0f;
}

void RenderPipeLine::RasterizeFace(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2)
{
	float x0 = get<0>(v0).x;
	float y0 = get<0>(v0).y;

	float x1 = get<0>(v1).x;
	float y1 = get<0>(v1).y;

	float x2 = get<0>(v2).x;
	float y2 = get<0>(v2).y;

	// 检测三角形是否为直线
	if (MathUtil::IsEqual(x0, x1) && MathUtil::IsEqual(x1, x2) || MathUtil::IsEqual(y0, y1) && MathUtil::IsEqual(y1, y2))
		return;

	// 设置扫描线起点x及终点x
	float xstart = x1;
	float xend = x2;

	// 设置扫描线起始y及终点y
	float ystart = y2;
	float yend = y0;

	// 计算三角形的高
	bool topface = y0 < y2;
	float dy = yend - ystart;
	float ddy = dy / std::abs(dy);

	float invdy = 1.0f / std::abs(dy);

	// 计算左斜边x积分
	float dxdyl = (x0 - x1) * invdy;

	// 计算右斜边x积分
	float dxdyr = (x0 - x2) * invdy;

	DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	for (float yi = ystart; topface ? (yi >= yend) : (yi <= yend); yi += ddy)
	{
		float invdx = 1.0f / (xend - xstart);

		for (float xi = xstart; xi <= xend; xi++)
		{
			// 绘制像素点
			RenderDevice::getSingletonPtr()->DrawPixel(std::lround(xi), std::lround(yi), color);
		}

		//计算下一条扫描线起点及终点
		xstart += dxdyl;
		xend += dxdyr;
	}
}

void RenderPipeLine::SetViewPortData(int width, int height)
{
	float alpha = (0.5f * width - 0.5f);
	float beta = (0.5f * height - 0.5f);

	m_ViewPortMatrix = Matrix(
		float4(alpha,	0.0f,	0.0f,	0.0f),
		float4(0.0f,   -beta,	0.0f,	0.0f),
		float4(0.0f,	0.0f,	1.0f,	0.0f),
		float4(alpha,	beta,	0.0f,	1.0f));
}
