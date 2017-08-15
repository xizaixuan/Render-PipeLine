#include "Engine.h"
#include "WinApp.h"
#include "RenderDevice.h"
#include <cstdlib>

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::init(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
	WinApp::getSingletonPtr()->create(hInstance, nCmdShow, width, height, "Tutorial1-Framework");

	RenderDevice::getSingletonPtr()->initRenderDevice(WinApp::getSingletonPtr()->getHwnd(), width, height);
}

void Engine::destroy()
{

}

void Engine::update(float dt)
{
	RenderDevice::getSingletonPtr()->renderBegin();

	drawLine(100, 100, 1024, 768);
	drawLine(600, 200, 200, 400);
	drawLine(500, 100, 500, 800);
	drawLine(100, 400, 800, 400);

	RenderDevice::getSingletonPtr()->renderBuffer();

	RenderDevice::getSingletonPtr()->renderEnd();
}

void Engine::drawLine(float startX, float startY, float endX, float endY)
{
	float x0 = startX;
	float y0 = startY;
	float x1 = endX;
	float y1 = endY;

	//DDAËã·¨
	float steps;
	float difX = x1 - x0;
	float difY = y1 - y0;
	if (abs(difX) > abs(difY))
		steps = abs(difX);
	else
		steps = abs(difY);

	float increx = difX / steps;
	float increy = difY / steps;

	float xi = x0;
	float yi = y0;

	for (int i = 1; i <= steps; i++)
	{
		DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

		// »æÖÆÏñËØµã
		RenderDevice::getSingletonPtr()->drawPixel((int)xi, (int)yi, color);

		xi += increx;
		yi += increy;
	}
}
