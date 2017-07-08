#include "RenderDevice.h"
#include <wingdi.h>

RenderDevice::RenderDevice(void)
	: mWindowWidth(0)
	, mWindowHeight(0)
	, mHWND(nullptr)
	, mZBuffer(nullptr)
	, mD2DFactory(nullptr)
	, mRenderTarget(nullptr)
	, mBitmap(nullptr)
	, mDataBuffer(nullptr)
{
}

RenderDevice::~RenderDevice(void)
{
	SAFE_RELEASE(mRenderTarget);
	SAFE_RELEASE(mD2DFactory);
	SAFE_RELEASE(mBitmap);

	if (mZBuffer != nullptr)
	{
		delete[] mZBuffer;
		mZBuffer = nullptr;
	}
}

void RenderDevice::initRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight)
{
	//进行赋值
	mWindowWidth = WindowWidth;
	mWindowHeight= WindowHeight;

	mHWND = hWndMain;

	if (mRenderTarget == nullptr)
	{
		HRESULT hr;

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mD2DFactory);
		if (FAILED(hr))
		{
			MessageBox(mHWND, "Create D2D factory failed!", "Error", 0);
			return;
		}

		D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_IGNORE
		);

		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties();
		props.pixelFormat = pixelFormat;

		hr = mD2DFactory->CreateHwndRenderTarget(
			props,
			D2D1::HwndRenderTargetProperties(mHWND, D2D1::SizeU(mWindowWidth, mWindowHeight)),
			&mRenderTarget
		);

		if (FAILED(hr))
		{
			MessageBox(mHWND, "Create render target failed!", "Error", 0);
			return;
		}

		//创建位图    
		D2D1_SIZE_U imgsize = D2D1::SizeU(mWindowWidth, mWindowHeight);
		D2D1_BITMAP_PROPERTIES prop =  
		{
			pixelFormat,
			(float)imgsize.width,
			(float)imgsize.height
		};
		long pitch = imgsize.width;
		mDataBuffer = new DWORD[imgsize.width * imgsize.height];
		memset(mDataBuffer, 0, imgsize.width * imgsize.height * sizeof(DWORD));
		mRenderTarget->CreateBitmap(imgsize, mDataBuffer, pitch, &prop, &mBitmap);
	}

	mZBuffer = new float[WindowWidth*WindowHeight];
}

void RenderDevice::renderBegin()
{
	mRenderTarget->BeginDraw();

	// 设置背景色
	mRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	memset(mDataBuffer, 0, mWindowWidth * mWindowHeight * sizeof(DWORD));
}

void RenderDevice::renderEnd()
{
	mRenderTarget->EndDraw();
}

void RenderDevice::renderBuffer()
{
	D2D1_RECT_U rect2 = D2D1::RectU(0, 0, mWindowWidth, mWindowHeight);
	mBitmap->CopyFromMemory(&rect2, mDataBuffer, mWindowWidth * sizeof(DWORD));
	mRenderTarget->DrawBitmap(mBitmap, D2D1::RectF(0.0f, 0.0f, mWindowWidth, mWindowHeight));
}

void RenderDevice::drawPixel(DWORD x, DWORD y, DWORD color)
{
	if (x < mWindowWidth && y < mWindowHeight)
	{
		int index = x + y*mWindowWidth;
		mDataBuffer[index] = color;
	}
}

void RenderDevice::drawPixel(DWORD x, DWORD y, DWORD color, float depth)
{
	if (x < mWindowWidth && y < mWindowHeight)
	{
		int index = x + y*mWindowWidth;
		mDataBuffer[index ] = color;

		if (depth < mZBuffer[index])
		{
			mZBuffer[index] = depth;
		}
	}
}