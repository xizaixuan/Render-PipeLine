#include "RenderDevice.h"
#include <wingdi.h>

RenderDevice::RenderDevice(void)
	: mWindowWidth(0)
	, mWindowHeight(0)
	, mPixelBuffer(nullptr)
	, mHDC(nullptr)
	, mCDC(nullptr)
	, mRenderBitMap(nullptr)
	, mHWND(nullptr)
	, mZBuffer(nullptr)
{
}

RenderDevice::~RenderDevice(void)
{
	mPixelBuffer = nullptr;

	DeleteDC(mCDC);
	ReleaseDC(mHWND, mHDC);

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

	mHDC = GetWindowDC(hWndMain);

	mCDC = CreateCompatibleDC(mHDC);

	// 配置BITMAPINFO信息
	BITMAPINFO bmpinfo;
	bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth = WindowWidth;
	bmpinfo.bmiHeader.biHeight = WindowHeight;
	bmpinfo.bmiHeader.biPlanes = 1;
	bmpinfo.bmiHeader.biBitCount = 32;
	bmpinfo.bmiHeader.biCompression = BI_RGB;
	bmpinfo.bmiHeader.biSizeImage = WindowWidth * WindowHeight * 32/8;
	bmpinfo.bmiHeader.biXPelsPerMeter = 0;
	bmpinfo.bmiHeader.biClrImportant = 0;
	bmpinfo.bmiHeader.biClrUsed = 0;

	// 申请内存, 无需手动释放
	mRenderBitMap = CreateDIBSection(mCDC, &bmpinfo, DIB_RGB_COLORS, (void**)&mPixelBuffer, NULL, 0);

	mZBuffer = new float[WindowWidth*WindowHeight];
}

void RenderDevice::renderBuffer()
{
	HGDIOBJ hOldSel = SelectObject(mCDC, mRenderBitMap);
 
	//将CompatibleDC的数据复制到屏幕显示DC中
	BitBlt(mHDC, 0, 0, mWindowWidth, mWindowHeight, mCDC, 0, 0, SRCCOPY);

	SelectObject(mCDC, hOldSel);
}

void RenderDevice::cleanBuffer()
{
	memset(mPixelBuffer, 0x00, sizeof(DWORD)*mWindowWidth*mWindowHeight);

	memset(mZBuffer, 0x7f, sizeof(float)*mWindowWidth*mWindowHeight);
}

void RenderDevice::drawPixel(DWORD x, DWORD y, DWORD color)
{
	if (x < mWindowWidth && y < mWindowHeight)
	{
		mPixelBuffer[x + (mWindowHeight-1-y)*mWindowWidth] = color;
	}
}

void RenderDevice::drawPixel(DWORD x, DWORD y, DWORD color, float depth)
{
	if (x < mWindowWidth && y < mWindowHeight)
	{
		int index = x + (mWindowHeight - 1 - y)*mWindowWidth;
		if (depth < mZBuffer[index])
		{
			mPixelBuffer[index] = color;
			mZBuffer[index] = depth;
		}
	}
}