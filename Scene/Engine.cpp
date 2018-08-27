#include "Engine.h"
#include "..\RenderPipeLine\Framework\WinApp.h"
#include "..\RenderPipeLine\Framework\RenderDevice.h"
#include "..\RenderPipeLine\Utility\PipeLineUtility.h"
#include "..\RenderPipeLine\Framework\Camera.h"

Engine::Engine()
	: m_pCamera(nullptr)
{
}

Engine::~Engine()
{
}

void Engine::Init(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
	WinApp::getSingletonPtr()->Create(hInstance, nCmdShow, width, height, "Render PipeLine");

	RenderDevice::getSingletonPtr()->InitRenderDevice(WinApp::getSingletonPtr()->GetHwnd(), width, height);

	RenderPipeLine::SetViewPortData(width, height);

	m_pCamera = new Camera();
	m_pCamera->SetParams(60, (float)width / (float)height, 0.1f, 1000.0f);
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
	m_pCamera->SetParams(Float3(100,100,100), float3(0,0,0));
	m_pCamera->BuildViewMatrix();
	m_pCamera->BuildPerspectiveMatrix();

	vector<float3> vertices {
		float3(-1.0f, -1.0f, -1.0f),
		float3(-1.0f,  1.0f, -1.0f),
		float3( 1.0f,  1.0f, -1.0f),
		float3( 1.0f, -1.0f, -1.0f),
		float3(-1.0f, -1.0f,  1.0f),
		float3(-1.0f,  1.0f,  1.0f),
		float3( 1.0f,  1.0f,  1.0f),
		float3( 1.0f, -1.0f,  1.0f)
	};

	vector<int> indices = {
		// Front face.
		0, 1, 2,
		0, 2, 3,

		// Back face.
		4, 6, 5,
		4, 7, 6,

		// Left face.
		4, 5, 1,
		4, 1, 0,

		// Right face.
		3, 2, 6,
		3, 6, 7,

		// Top face.
		1, 5, 6,
		1, 6, 2,

		// Bottom face.
		4, 0, 3,
		4, 3, 7,
	};

	RenderPipeLine::PipeLine(m_pCamera, vertices, indices);
}
