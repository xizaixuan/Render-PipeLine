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

void Engine::Init(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
	WinApp::getSingletonPtr()->Create(hInstance, nCmdShow, width, height, "Render PipeLine");

	RenderDevice::getSingletonPtr()->InitRenderDevice(WinApp::getSingletonPtr()->GetHwnd(), width, height);
}

void Engine::Destroy()
{

}

void Engine::Update(float dt)
{
	RenderDevice::getSingletonPtr()->RenderBegin();

	RenderScene();

	RenderDevice::getSingletonPtr()->RenderBuffer();

	RenderDevice::getSingletonPtr()->RenderEnd();
}

void Engine::RenderScene()
{
	DWORD color = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	PipeLine::drawLine(50, 50, 500, 500, color, DrawLineType::DDA);
	PipeLine::drawLine(50 + 50, 50, 500 + 50, 500, color, DrawLineType::Bresenham);
}
