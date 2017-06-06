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
{
}

RenderDevice::~RenderDevice(void)
{
	mPixelBuffer = nullptr;

	DeleteDC(mCDC);
	ReleaseDC(mHWND, mHDC);
}

void RenderDevice::initRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight)
{
	//���и�ֵ
	mWindowWidth = WindowWidth;
	mWindowHeight= WindowHeight;

	mHWND = hWndMain;

	mHDC = GetWindowDC(hWndMain);

	mCDC = CreateCompatibleDC(mHDC);

	// ����BITMAPINFO��Ϣ
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

	// �����ڴ�, �����ֶ��ͷ�
	mRenderBitMap = CreateDIBSection(mCDC, &bmpinfo, DIB_RGB_COLORS, (void**)&mPixelBuffer, NULL, 0);
}

void RenderDevice::renderBuffer()
{
	HGDIOBJ hOldSel = SelectObject(mCDC, mRenderBitMap);
 
	//��CompatibleDC�����ݸ��Ƶ���Ļ��ʾDC��
	BitBlt(mHDC, 0, 0, mWindowWidth, mWindowHeight, mCDC, 0, 0, SRCCOPY);

	SelectObject(mCDC, hOldSel);
}

void RenderDevice::cleanBuffer()
{
	memset(mPixelBuffer, 0, sizeof(DWORD)*mWindowWidth*mWindowHeight);
}

void RenderDevice::drawPixel(DWORD x, DWORD y, DWORD color)
{
	mPixelBuffer[x+y*mWindowWidth] = color;
}