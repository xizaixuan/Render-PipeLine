#include "PipeLineUtility.h"
#include "..\Framework\RenderDevice.h"

void drawLineWithDDA(float startX, float startY, float endX, float endY)
{
	//DDAÀ„∑®

	float x0 = startX;
	float y0 = startY;
	float x1 = endX;
	float y1 = endY;

	float difX = x1 - x0;
	float difY = y1 - y0;
	float steps = std::max<float>(std::abs(difX), std::abs(difY));

	float increx = difX / steps;
	float increy = difY / steps;

	float xi = startX;
	float yi = startY;

	for (int i = 0; i < steps; i++)
	{
		DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

		// ªÊ÷∆œÒÀÿµ„
		RenderDevice::getSingletonPtr()->drawPixel((int)xi, (int)yi, color);

		xi += increx;
		yi += increy;
	}
}

void drawLineWithBresenham(float startX, float startY, float endX, float endY)
{
}
