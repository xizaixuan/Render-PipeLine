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

		Rasterize(tuple<float4>(v0), tuple<float4>(v1), tuple<float4>(v2));

// 		DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;
// 		DrawLine(v0.x, v0.y, v1.x, v1.y, color, DrawLineType::DDA);
// 		DrawLine(v0.x, v0.y, v2.x, v2.y, color, DrawLineType::DDA);
// 		DrawLine(v1.x, v1.y, v2.x, v2.y, color, DrawLineType::DDA);
	}
}

void RenderPipeLine::SplitTriangle(float4& v0, float4& v1, float4& v2, float4& v3, float4& v4, float4& v5)
{
	float x0 = v0.x;
	float x1 = v1.x;
	float x2 = v2.x;
	float y0 = v0.y;
	float y1 = v1.y;
	float y2 = v2.y;

	float dy1_0 = y1 - y0;
	float dy2_0 = y2 - y0;
	float dx2_0 = x2 - x0;

	// dx(new-0)/dx(2-0) = dy(1-0)/dy(2-0) => newX = 0 + dy(1-0)/dy(2-0)*dx(2-0)
	float newX = x0 + (dy1_0 / dy2_0)*dx2_0;

	//////////////////////////////////////////////////////////////////////////
	// 平底三角形
	v0 = float4(x0, y0, v0.z, 1);
	v1 = float4(newX, y1, v1.z, 1);
	v2 = float4(x1, y1, v2.z, 1);

	//////////////////////////////////////////////////////////////////////////
	// 平顶三角形
	v3 = float4(x1, y1, v0.z, 1);
	v4 = float4(newX, y1, v1.z, 1);
	v5 = float4(x2, y2, v2.z, 1);
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
		/*float4 v3(0.0f, 0.0f, 0.0f, 0.0f);
		float4 v4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 v5(0.0f, 0.0f, 0.0f, 0.0f);

		// 分裂三角形
		SplitTriangle(position0, position1, position2, v3, v4, v5);

		// 平底三角形
		if (position2.get().x < position1.get().x)
		{
			//std::swap(position1, positoin2);
			std::swap(v2, v1);

		}
		RasterizeBottomFace(position0, position1, position2);

		// 平顶三角形
		if (v4.x < v3.x)
		{
			std::swap(v4, v3);
		}
		RasterizeTopFace(v3, v4, v5);*/
	}
}

void RenderPipeLine::RasterizeTopFace(float4 v0, float4 v1, float4 v2)
{
	float x0 = v0.x;
	float y0 = v0.y;

	float x1 = v1.x;
	float y1 = v1.y;

	float x2 = v2.x;
	float y2 = v2.y;

	// 检测三角形是否退出为直线
	if (((x0 == x1) && (x1 == x2)) || ((y0 == y1) && (y1 == y2)))
		return;

	// 计算三角形的高
	float dy = (y2 - y0);

	float inv_dy = 1.0f / dy;

	// 计算左斜边x积分
	float dxdyl = (x2 - x0) * inv_dy;

	// 计算右斜边x积分
	float dxdyr = (x2 - x1) * inv_dy;

	// 设置扫描线起点x及终点x
	float xstart = x0;
	float xend = x1;

	// 设置扫描线起始y及终点y
	float ystart = y0;
	float yend = y2;

	DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	for (float yi = ystart; yi < yend; yi++)
	{
		float inv_dx = 1.0f / (xend - xstart);

		// 绘制扫描线
		for (float xi = xstart; xi < xend; xi++)
		{
			// 绘制像素点
			RenderDevice::getSingletonPtr()->DrawPixel(std::lround(xi), std::lround(yi), color);
		}

		//计算下一条扫描线起点及终点
		xstart += dxdyl;
		xend += dxdyr;
	}
}

void RenderPipeLine::RasterizeBottomFace(float4 v0, float4 v1, float4 v2)
{
	float x0 = v0.x;
	float y0 = v0.y;

	float x1 = v1.x;
	float y1 = v1.y;

	float x2 = v2.x;
	float y2 = v2.y;

	// 检测三角形是否退出为直线
	if (((x0 == x1) && (x1 == x2)) || ((y0 == y1) && (y1 == y2)))
		return;

	// 计算三角形的高
	float dy = (y2 - y0);

	float inv_dy = 1.0f / dy;

	// 计算左斜边x积分
	float dxdyl = (x1 - x0) * inv_dy;

	// 计算右斜边x积分
	float dxdyr = (x2 - x0) * inv_dy;

	// 设置扫描线起点x及终点x
	float xstart = x0;
	float xend = x0;

	// 设置扫描线起始y及终点y
	float ystart = y0;
	float yend = y2;

	DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	for (float yi = ystart; yi < yend; yi++)
	{
		float inv_dx = 1.0f / (xend - xstart);

		// 绘制扫描线
		for (float xi = xstart; xi < xend; xi++)
		{
			RenderDevice::getSingletonPtr()->DrawPixel(std::lround(xi), std::lround(yi), color);
		}

		//计算下一条扫描线起点及终点
		xstart += dxdyl;
		xend += dxdyr;
	}
}

void RenderPipeLine::RasterizeFace(float4 v0, float4 v1, float4 v2)
{
	float x0 = v0.x;
	float y0 = v0.y;

	float x1 = v1.x;
	float y1 = v1.y;

	float x2 = v2.x;
	float y2 = v2.y;

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
	float dy = std::abs(yend - ystart);
	int idy = std::lround(dy);
	float ddy = (yend - ystart) / idy;

	float invdy = 1.0f / dy;

	// 计算左斜边x积分
	float dxdyl = (x0 - x1) * invdy;

	// 计算右斜边x积分
	float dxdyr = (x0 - x2) * invdy;

	DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	float yi = ystart;
	for (int i = 0; i < idy; i++)
	{
		float invdx = 1.0f / (xend - xstart);

		// 绘制扫描线
		for (float xi = xstart; xi < xend; xi++)
		{
			// 绘制像素点
			RenderDevice::getSingletonPtr()->DrawPixel(std::lround(xi), std::lround(yi), color);
		}

		//计算下一条扫描线起点及终点
		xstart += dxdyl;
		xend += dxdyr;
		yi += ddy;
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
