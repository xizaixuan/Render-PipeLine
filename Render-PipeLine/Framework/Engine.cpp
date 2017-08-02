#include "Engine.h"
#include "WinApp.h"
#include "RenderDevice.h"

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

	RenderDevice::getSingletonPtr()->renderBuffer();

	RenderDevice::getSingletonPtr()->renderEnd();
}