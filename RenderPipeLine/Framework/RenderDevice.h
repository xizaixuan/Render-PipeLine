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




class RenderDevice : public Singleton <RenderDevice>
{
	SINGLETON_DEFINE(RenderDevice)
private:
	RenderDevice(void);
	~RenderDevice(void);

public:
	/// \brief 初始化渲染设备
	void InitRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight);

	/// brief 渲染开始
	void RenderBegin();

	/// brief 渲染结束
	void RenderEnd();

	/// \brief 更新Buffer
	void RenderBuffer();
	
	/// \brief 绘制color
	void DrawPixel(DWORD x, DWORD y, DWORD color);

private:
	///	窗口宽度
	DWORD	m_WindowWidth;

	///	窗口高度
	DWORD	m_WindowHeight;

	///	窗口句柄
	HWND	m_HWND;

	/// 实例工厂
	ID2D1Factory*			m_pD2DFactory;

	/// 渲染目标
	ID2D1HwndRenderTarget*	m_pRenderTarget;

	/// 位图
	ID2D1Bitmap*			m_pBitmap;

	/// 渲染数据
	DWORD*					m_pDataBuffer;
};

#endif
