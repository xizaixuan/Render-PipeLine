/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   ������
/// \author  xizaixuan
/// \date    2017-07
/////////////////////////////////////////////////////////////////////////////////
#ifndef _RenderDevice_H_
#define _RenderDevice_H_

#include <windows.h>
#include <D2D1_1.h>
#include "..\Utility\Singleton.h"




class RenderDevice :public Singleton <RenderDevice>
{
	SINGLETON_DEFINE(RenderDevice)
private:
	RenderDevice(void);
	~RenderDevice(void);

public:
	/// \brief ��ʼ����Ⱦ�豸
	void initRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight);

	/// brief ��Ⱦ��ʼ
	void renderBegin();

	/// brief ��Ⱦ����
	void renderEnd();

	/// \brief ����Buffer
	void renderBuffer();
	
	/// \brief ����color
	void drawPixel(DWORD x, DWORD y, DWORD color);

private:
	///	���ڿ��
	DWORD	m_WindowWidth;

	///	���ڸ߶�
	DWORD	m_WindowHeight;

	///	���ھ��
	HWND	m_HWND;

	/// ʵ������
	ID2D1Factory*			m_D2DFactory;

	/// ��ȾĿ��
	ID2D1HwndRenderTarget*	m_RenderTarget;

	/// λͼ
	ID2D1Bitmap*			m_Bitmap;

	/// ��Ⱦ����
	DWORD*					m_DataBuffer;
};

#endif
