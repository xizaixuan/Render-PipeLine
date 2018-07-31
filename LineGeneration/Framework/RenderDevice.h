/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   绘制类
/// \author  xizaixuan
/// \date    2017-07
/////////////////////////////////////////////////////////////////////////////////
#ifndef _RenderDevice_H_
#define _RenderDevice_H_

#include <windows.h>
#include <D2D1_1.h>
#include "..\Utility\Singleton.h"


#define SAFE_RELEASE(P) if(P != nullptr){P->Release() ; P = nullptr;}
#define SAFE_DELETE(P) if(P != nullptr){delete P; P = nullptr;}
#define SAFE_DELETE_ARRAY(P) if(P != nullptr){delete[] P; P = nullptr;}

class RenderDevice :public Singleton <RenderDevice>
{
	SINGLETON_DEFINE(RenderDevice)
private:
	RenderDevice(void);
	~RenderDevice(void);

public:
	/// \brief 初始化渲染设备
	void initRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight);

	/// brief 渲染开始
	void renderBegin();

	/// brief 渲染结束
	void renderEnd();

	/// \brief 更新Buffer
	void renderBuffer();
	
	/// \brief 绘制color
	void drawPixel(DWORD x, DWORD y, DWORD color);

private:
	///	窗口宽度
	DWORD	mWindowWidth;

	///	窗口高度
	DWORD	mWindowHeight;

	///	窗口句柄
	HWND	mHWND;

	/// 实例工厂
	ID2D1Factory*			mD2DFactory;

	/// 渲染目标
	ID2D1HwndRenderTarget*	mRenderTarget;

	/// 位图
	ID2D1Bitmap*			mBitmap;

	/// 渲染数据
	DWORD*					mDataBuffer;
};

#endif
