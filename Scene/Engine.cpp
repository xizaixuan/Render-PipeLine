#include "Engine.h"
#include "..\RenderPipeLine\Framework\WinApp.h"
#include "..\RenderPipeLine\Framework\RenderDevice.h"
#include "..\RenderPipeLine\Utility\PipeLineUtility.h"
#include "..\RenderPipeLine\Framework\Camera.h"
#include <windowsx.h>
#include "..\RenderPipeLine\Mathematics\MathUtil.h"
#include "fbxsdk.h"
#include "FbxLoader.h"
#include "..\RenderPipeLine\Utility\RenderContext.h"

vector<float3> vertices;
vector<int> indices;

Engine::Engine()
	: m_pCamera(nullptr)
	, m_pRenderContext(nullptr)
	, m_Theta(-MathUtil::pi * 0.5f)
	, m_Phi(MathUtil::pi * 0.5f)
	, m_Radius(800.0f)
	, m_LastMousePos(0.0f, 0.0f)
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

	m_pRenderContext = new RenderContext();

	//////////////////////////////////////////////////////////////////////////

	const char* filename = "D:\\ProjectZone\\RenderPipeLine\\untitled.fbx";

	FbxLoader::getSingletonPtr()->LoadScene(filename, m_RenderBuffers);
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
	float x = m_Radius * sinf(m_Phi)*cosf(m_Theta);
	float z = m_Radius * sinf(m_Phi)*sinf(m_Theta);
	float y = m_Radius * cosf(m_Phi);

	m_pCamera->SetParams(Float3(x, y, z), float3(0, 0, 0));
	m_pCamera->BuildViewMatrix();
	m_pCamera->BuildPerspectiveMatrix();

	m_pRenderContext->CameraPosition = m_pCamera->m_Position;
	m_pRenderContext->ViewMatrix = m_pCamera->GetViewMatrix();
	m_pRenderContext->ProjMatrix = m_pCamera->GetPerspectiveMatrix();

	for (auto buffer : m_RenderBuffers)
	{
		RenderPipeLine::DrawCall(
			m_pRenderContext,
			buffer.vertices,
			buffer.indices,
			buffer.normals);
	}
}

void Engine::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		float dx = MathUtil::AngelToRadian(0.25f*static_cast<float>(x - m_LastMousePos.x));
		float dy = MathUtil::AngelToRadian(0.25f*static_cast<float>(y - m_LastMousePos.y));

		// Update angles based on input to orbit camera around box.
		m_Theta += dx;
		m_Phi += dy;

		// Restrict the angle mPhi.
		m_Phi = MathUtil::Clamp(m_Phi, 0.1f, MathUtil::pi - 0.1f);
	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		// Make each pixel correspond to 0.005 unit in the scene.
		float dx = 0.005f*static_cast<float>(x - m_LastMousePos.x);
		float dy = 0.005f*static_cast<float>(y - m_LastMousePos.y);

		// Update the camera radius based on input.
		m_Radius += dx - dy;

		// Restrict the radius.
		m_Radius = MathUtil::Clamp(m_Radius, 3.0f, 15.0f);
	}

	m_LastMousePos.x = static_cast<float>(x);
	m_LastMousePos.y = static_cast<float>(y);
}
