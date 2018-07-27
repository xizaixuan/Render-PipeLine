#include "Engine.h"
#include "WinApp.h"
#include "RenderDevice.h"
#include <cstdlib>

#include<algorithm>

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

	drawLineWithDDA(100, 100, 1024, 768);
	drawLineWithDDA(600, 200, 200, 400);
	drawLineWithDDA(500, 100, 500, 800);
	drawLineWithDDA(100, 400, 800, 400);

	RenderDevice::getSingletonPtr()->renderBuffer();

	RenderDevice::getSingletonPtr()->renderEnd();
}

void Engine::drawLineWithDDA(float startX, float startY, float endX, float endY)
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

void Engine::drawLineWithBresenham(float startX, float startY, float endX, float endY)
{
}
