#include "Engine.h"
#include "WinApp.h"
#include "RenderDevice.h"

Engine::Engine(void)
{
}


Engine::~Engine(void)
{
}


void Engine::init(HINSTANCE hInstance, int nCmdShow)
{
	WinApp::getSingletonPtr()->create(hInstance, nCmdShow, 1024, 768, "SoftPipeLine");

	RenderDevice::getSingletonPtr()->initRenderDevice(WinApp::getSingletonPtr()->getHwnd(), 1024, 768);
}


void Engine::destroy()
{

}


void Engine::update(float dt)
{
	RenderDevice::getSingletonPtr()->cleanBuffer();

	RenderDevice::getSingletonPtr()->renderBuffer();
}