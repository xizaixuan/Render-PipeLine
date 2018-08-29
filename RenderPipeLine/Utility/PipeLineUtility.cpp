#include "PipeLineUtility.h"
#include "..\Framework\RenderDevice.h"
#include "..\Mathematics\Matrix.h"
#include "..\Framework\Camera.h"
#include "..\Mathematics\MathUtil.h"
#include "..\Mathematics\Float4.h"

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

void RenderPipeLine::PipeLine(Camera* camera, vector<float3> vertices, vector<int> indices)
{
	auto viewMat = camera->GetViewMatrix();
	auto projMat = camera->GetPerspectiveMatrix();
	auto vp = viewMat * projMat;

	auto indexLength = indices.size();
	for (int index = 0; index < indexLength; index +=3 )
	{
		auto v0 = float4(vertices[indices[index + 0]], 1.0f);
		auto v1 = float4(vertices[indices[index + 1]], 1.0f);
		auto v2 = float4(vertices[indices[index + 2]], 1.0f);

		v0 = v0 * vp;
		v1 = v1 * vp;
		v2 = v2 * vp;

		v0 = MathUtil::Homogenous(v0);
		v1 = MathUtil::Homogenous(v1);
		v2 = MathUtil::Homogenous(v2);

		v0 = v0 * m_ViewPortMatrix;
		v1 = v1 * m_ViewPortMatrix;
		v2 = v2 * m_ViewPortMatrix;

		DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;
		DrawLine(v0.x, v0.y, v1.x, v1.y, color, DrawLineType::DDA);
		DrawLine(v0.x, v0.y, v2.x, v2.y, color, DrawLineType::DDA);
		DrawLine(v1.x, v1.y, v2.x, v2.y, color, DrawLineType::DDA);
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
