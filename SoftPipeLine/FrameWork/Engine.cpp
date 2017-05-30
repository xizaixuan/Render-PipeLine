#include "Engine.h"
#include "WinApp.h"

Engine::Engine(void)
{
}


Engine::~Engine(void)
{
}


void Engine::init(HINSTANCE hInstance, int nCmdShow)
{
	createWin(hInstance,nCmdShow);
}


void Engine::destroy()
{

}


void Engine::update(float dt)
{
	
}


void Engine::createWin(HINSTANCE hInstance, int nCmdShow)
{
	WinApp::getSingletonPtr()->create(hInstance, nCmdShow, 1024, 768, "SoftPipeLine");
}