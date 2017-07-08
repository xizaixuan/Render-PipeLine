/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ������
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _RenderDevice_H_
#define _RenderDevice_H_

#include <windows.h>
#include <D2D1_1.h>
#include "../Util/Singleton.h"

#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}

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

	/// \brief ����color
	void drawPixel(DWORD x, DWORD y, DWORD color, float depth);

private:
	/// ��Ȼ���
	float*	mZBuffer;

	///	���ڿ��
	DWORD	mWindowWidth;

	///	���ڸ߶�
	DWORD	mWindowHeight;

	///	���ھ��
	HWND	mHWND;

	/// ʵ������
	ID2D1Factory*			mD2DFactory;

	/// ��ȾĿ��
	ID2D1HwndRenderTarget*	mRenderTarget;

	/// λͼ
	ID2D1Bitmap*			mBitmap;

	/// ��Ⱦ����
	DWORD*					mDataBuffer;
};

#endif
