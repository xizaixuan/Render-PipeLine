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
	, mRadius(5.0f)
	, mPhi(1.0f)
	, mTheta(1.0f)
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
	WinApp::getSingletonPtr()->create(hInstance, nCmdShow, 1024.0f, 768.0f, "SoftPipeLine");

	RenderDevice::getSingletonPtr()->initRenderDevice(WinApp::getSingletonPtr()->getHwnd(), 1024.0f, 768.0f);

	PipeLine::getSingletonPtr()->setViewPortData(1024.0f, 768.0f);

	mCamera = new Camera();

	mCamera->update(60, 1024.0f / 768.0f, 0.1f, 1000.0f);


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
	RenderDevice::getSingletonPtr()->renderBegin();

	updateCamera(dt);

	PipeLine::getSingletonPtr()->execute(mCamera);

	RenderDevice::getSingletonPtr()->renderBuffer();

	RenderDevice::getSingletonPtr()->renderEnd();
}


void Engine::OnMouseDown(WPARAM btnState, int x, int y)
{
}

void Engine::OnMouseUp(WPARAM btnState, int x, int y)
{
}

void Engine::OnMouseMove(WPARAM btnState, int x, int y)
{
	auto Clamp = [](float num, float min, float max)
	{
		if (num<= min)
		{
			return min;
		}
		else if (num>= max)
		{
			return max;
		}
		else
		{
			return num;
		}
	};

	if ((btnState & MK_LBUTTON) != 0)
	{
		auto DEG2RAD = [](float degree)
		{
			return PI / 180.0f * degree;
		};

		// Make each pixel correspond to a quarter of a degree.
		float dx = DEG2RAD(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = DEG2RAD(0.25f*static_cast<float>(y - mLastMousePos.y));

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi += dy;

		// Restrict the angle mPhi.
		mPhi = Clamp(mPhi, 0.1f, PI - 0.1f);
	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		// Make each pixel correspond to 0.005 unit in the scene.
		float dx = 0.005f*static_cast<float>(x - mLastMousePos.x);
		float dy = 0.005f*static_cast<float>(y - mLastMousePos.y);

		// Update the camera radius based on input.
		mRadius += dx - dy;

		// Restrict the radius.
		mRadius = Clamp(mRadius, 1.0f, 15.0f);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}


void Engine::updateCamera(float dt)
{
	// Convert Spherical to Cartesian coordinates.
	float x = mRadius*sinf(mPhi)*cosf(mTheta);
	float z = mRadius*sinf(mPhi)*sinf(mTheta);
	float y = mRadius*cosf(mPhi);

	// Build the view matrix.
	Vector3 pos		= Vector3(x, y, z);
	Vector3 target	= Vector3(0.0f, 0.0f, 0.0f);

	mCamera->update(pos, target);
}