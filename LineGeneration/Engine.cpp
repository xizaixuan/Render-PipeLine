#include "Engine.h"
#include "..\RenderPipeLine\Framework\WinApp.h"
#include "..\RenderPipeLine\Framework\RenderDevice.h"
#include "..\RenderPipeLine\Utility\PipeLineUtility.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::init(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
	WinApp::getSingletonPtr()->create(hInstance, nCmdShow, width, height, "Render PipeLine");

	RenderDevice::getSingletonPtr()->initRenderDevice(WinApp::getSingletonPtr()->getHwnd(), width, height);
}

void Engine::destroy()
{

}

void Engine::update(float dt)
{
	RenderDevice::getSingletonPtr()->renderBegin();

	renderScene();

	RenderDevice::getSingletonPtr()->renderBuffer();

	RenderDevice::getSingletonPtr()->renderEnd();
}

void Engine::renderScene()
{
	DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	PipeLine::drawLine(50, 50, 500, 500, color, DrawLineType::DDA);
	PipeLine::drawLine(50 + 50, 50, 500 + 50, 500, color, DrawLineType::Bresenham);
}
