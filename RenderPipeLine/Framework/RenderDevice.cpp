#include "RenderDevice.h"
#include <wingdi.h>
#include "..\Utility\PipeLineUtility.h"

RenderDevice::RenderDevice(void)
	: m_WindowWidth(0)
	, m_WindowHeight(0)
	, m_HWND(nullptr)
	, m_pD2DFactory(nullptr)
	, m_pRenderTarget(nullptr)
	, m_pBitmap(nullptr)
	, m_pDataBuffer(nullptr)
{
}

RenderDevice::~RenderDevice(void)
{
	SAFE_DELETE_ARRAY(m_pDataBuffer);

	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pD2DFactory);
	SAFE_RELEASE(m_pBitmap);
}

void RenderDevice::InitRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight)
{
	//进行赋值
	m_WindowWidth = WindowWidth;
	m_WindowHeight= WindowHeight;

	m_HWND = hWndMain;

	if (m_pRenderTarget == nullptr)
	{
		HRESULT hr;

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
		if (FAILED(hr))
		{
			MessageBox(m_HWND, "Create D2D factory failed!", "Error", 0);
			return;
		}

		D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_IGNORE
		);

		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties();
		props.pixelFormat = pixelFormat;

		hr = m_pD2DFactory->CreateHwndRenderTarget(
			props,
			D2D1::HwndRenderTargetProperties(m_HWND, D2D1::SizeU(m_WindowWidth, m_WindowHeight)),
			&m_pRenderTarget
		);

		if (FAILED(hr))
		{
			MessageBox(m_HWND, "Create render target failed!", "Error", 0);
			return;
		}

		//创建位图    
		D2D1_SIZE_U imgsize = D2D1::SizeU(m_WindowWidth, m_WindowHeight);
		D2D1_BITMAP_PROPERTIES prop =  
		{
			pixelFormat,
			(float)imgsize.width,
			(float)imgsize.height
		};
		long pitch = imgsize.width;
		m_pDataBuffer = new DWORD[imgsize.width * imgsize.height];
		memset(m_pDataBuffer, 0, imgsize.width * imgsize.height * sizeof(DWORD));
		m_pRenderTarget->CreateBitmap(imgsize, m_pDataBuffer, pitch, &prop, &m_pBitmap);
	}
}

void RenderDevice::RenderBegin()
{
	m_pRenderTarget->BeginDraw();

	// 设置背景色
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	memset(m_pDataBuffer, 0, m_WindowWidth * m_WindowHeight * sizeof(DWORD));
}

void RenderDevice::RenderEnd()
{
	m_pRenderTarget->EndDraw();
}

void RenderDevice::RenderBuffer()
{
	D2D1_RECT_U rect2 = D2D1::RectU(0, 0, m_WindowWidth, m_WindowHeight);
	m_pBitmap->CopyFromMemory(&rect2, m_pDataBuffer, m_WindowWidth * sizeof(DWORD));
	m_pRenderTarget->DrawBitmap(m_pBitmap, D2D1::RectF(0.0f, 0.0f, m_WindowWidth-1.0f, m_WindowHeight-1.0f));
}

void RenderDevice::DrawPixel(DWORD x, DWORD y, DWORD color)
{
	if (x < m_WindowWidth && y < m_WindowHeight)
	{
		auto index = x + y*m_WindowWidth;
		m_pDataBuffer[index] = color;
	}
}