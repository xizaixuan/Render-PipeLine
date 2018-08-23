#include "PipeLineUtility.h"
#include "..\Framework\RenderDevice.h"

void PipeLine::drawLine(float startX, float startY, float endX, float endY, DWORD color, DrawLineType type)
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
			RenderDevice::getSingletonPtr()->DrawPixel(std::round(xi), std::round(yi), color);

			xi += increx;
			yi += increy;
		}
	}
	break;
	case Bresenham:
	{
		int dx = endX - startX;
		int dy = endY - startY;

		int ux = (dx > 0) ? 1 : -1;
		int uy = (dy > 0) ? 1 : -1;

		int xi = startX;
		int yi = startY;

		int eps = 0.0f;
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
