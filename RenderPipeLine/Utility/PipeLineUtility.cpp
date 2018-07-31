#include "PipeLineUtility.h"
#include "..\Framework\RenderDevice.h"

void PipeLine::drawLine(float startX, float startY, float endX, float endY, DWORD color, DrawLineType type)
{
	//DDAÀ„∑®
	float difX = endX - startX;
	float difY = endY - startY;
	float steps = std::max<float>(std::abs(difX), std::abs(difY));

	float increx = difX / steps;
	float increy = difY / steps;

	float xi = startX;
	float yi = startY;

	for (int i = 0; i < steps; i++)
	{
		RenderDevice::getSingletonPtr()->drawPixel((int)xi, (int)yi, color);

		xi += increx;
		yi += increy;
	}
}
