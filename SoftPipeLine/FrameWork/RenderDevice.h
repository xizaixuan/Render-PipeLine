/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   绘制类
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _RenderDevice_H_
#define _RenderDevice_H_

#include <windows.h>
#include "../Util/Singleton.h"

class RenderDevice :public Singleton <RenderDevice>
{
	SINGLETON_DEFINE(RenderDevice)
private:
	RenderDevice(void);
	~RenderDevice(void);

public:
	/// \brief 初始化渲染设备
	void initRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight);

	/// \brief 更新Buffer
	void renderBuffer();

	/// \brief 清空Buffer
	void cleanBuffer();
	
	/// \brief 绘制color
	void drawPixel(DWORD x, DWORD y, DWORD color);

private:
	///	像素Buffer
	DWORD*	mPixelBuffer;

	///	窗口宽度
	DWORD	mWindowWidth;

	///	窗口高度
	DWORD	mWindowHeight;

	///	窗口设备环境句柄
	HDC		mHDC;

	///	窗口兼容设备环境句柄
	HDC		mCDC;

	/// 渲染位图句柄
	HBITMAP mRenderBitMap;

	///	窗口句柄
	HWND	mHWND;

};


#endif
