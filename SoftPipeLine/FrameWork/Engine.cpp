#include "Engine.h"
#include "WinApp.h"
#include "RenderDevice.h"
#include "..\RenderCore\Camera.h"
#include "..\RenderCore\RenderFace.h"
#include "..\RenderCore\PipeLine.h"
#include "..\Math\MathUtil.h"
#include "..\RenderCore\Texture.h"
#include "..\RenderCore\RenderUtil.h"

Engine::Engine()
	: mCamera(nullptr)
{
}

Engine::~Engine()
{
	if (mCamera != nullptr)
	{
		delete mCamera;
		mCamera = nullptr;
	}
}

Texture* texture = nullptr;
void Engine::init(HINSTANCE hInstance, int nCmdShow)
{
	WinApp::getSingletonPtr()->create(hInstance, nCmdShow, 1024, 768, "SoftPipeLine");

	RenderDevice::getSingletonPtr()->initRenderDevice(WinApp::getSingletonPtr()->getHwnd(), 1024, 768);

	PipeLine::getSingletonPtr()->setViewPortData(1024.0f, 768.0f);

	mCamera = new Camera();

	mCamera->update(60, 1024.0f/768.0f, 1.0f, 100.0f);


	//////////////////////////////////////////////////////////////////////////
	// cube model
	Vector4 cubeVertexArray[] = {
		Vector4(-1.0f,-1.0f,-1.0f),
		Vector4(-1.0f, 1.0f,-1.0f),
		Vector4( 1.0f, 1.0f,-1.0f),
		Vector4( 1.0f,-1.0f,-1.0f),
		Vector4(-1.0f,-1.0f, 1.0f),
		Vector4(-1.0f, 1.0f, 1.0f),
		Vector4( 1.0f, 1.0f, 1.0f),
		Vector4( 1.0f,-1.0f, 1.0f)
	};

	int k[36] = {0};
	Vector2 UV[36] = { Vector2(0.0f, 0.0f) };

	for (int i=0;i<36;i+=6)
	{
		UV[i] = Vector2(0.0f, 1.0f);  UV[i+1] = Vector2(0.0f, 0.0f); UV[i+2] = Vector2(1.0f, 0.0f);
		UV[i+3] = Vector2(0.0f, 1.0f);  UV[i+4] = Vector2(1.0f, 0.0f); UV[i+5] = Vector2(1.0f, 1.0f);
	}

	// Front face.
	k[0] = 0; k[1] = 1; k[2] = 2;
	k[3] = 0; k[4] = 2; k[5] = 3;

	// Back face.
	k[6] = 4; k[7] = 6; k[8] = 5;
	k[9] = 4; k[10] = 7; k[11] = 6;

	// Left face.
	k[12] = 4; k[13] = 5; k[14] = 1;
	k[15] = 4; k[16] = 1; k[17] = 0;

	// Right face.
	k[18] = 3; k[19] = 2; k[20] = 6;
	k[21] = 3; k[22] = 6; k[23] = 7;

	// Top face.
	k[24] = 1; k[25] = 5; k[26] = 6;
	k[27] = 1; k[28] = 6; k[29] = 2;

	// Bottom face.
	k[30] = 4; k[31] = 0; k[32] = 3;
	k[33] = 4; k[34] = 3; k[35] = 7;

	for (int i=0;i<36;i+=3)
	{
		RenderFace face;
		face.v0 = cubeVertexArray[k[i]];
		face.v1 = cubeVertexArray[k[i+1]];
		face.v2 = cubeVertexArray[k[i+2]];

		face.uv0 = UV[i];
		face.uv1 = UV[i+1];
		face.uv2 = UV[i+2];

		PipeLine::getSingletonPtr()->addToRenderList(face);
	}

	texture = LoadTextureFromPNG("Texture/BoxTexture.bmp");
}

void Engine::destroy()
{

}

void Engine::update(float dt)
{
	RenderDevice::getSingletonPtr()->cleanBuffer();

	updateCamera(dt);

	PipeLine::getSingletonPtr()->execute(mCamera);

	RenderDevice::getSingletonPtr()->renderBuffer();
}

/// \brief 相机数据更新
void Engine::updateCamera(float dt)
{
	static float theta = 0.0f;
	static float radius = 4.0;

	static Vector3 position(4.0f, 0.0f, 0.0f);
	static Vector3 target(0.0f, 0.0f, 0.0f);

	static POINT last;

	POINT pt;
	GetCursorPos(&pt);

	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		theta -= dt*(pt.x - last.x);
	}

	if (GetKeyState(VK_MBUTTON) & 0x8000)
	{
		float dx = dt*static_cast<float>(pt.x - last.x);
		float dy = dt*static_cast<float>(pt.y - last.y);

		radius += dx - dy;

		radius = max(radius, 0);
	}

	last = pt;

	position.x = radius*cosf(theta);
	position.z = radius*sinf(theta);

	mCamera->update(position, target);
}