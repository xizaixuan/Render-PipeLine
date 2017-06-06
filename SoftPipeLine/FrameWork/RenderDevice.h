/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   ������
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
	/// \brief ��ʼ����Ⱦ�豸
	void initRenderDevice(HWND hWndMain,int WindowWidth,int WindowHeight);

	/// \brief ����Buffer
	void renderBuffer();

	/// \brief ���Buffer
	void cleanBuffer();
	
	/// \brief ����color
	void drawPixel(DWORD x, DWORD y, DWORD color);

private:
	///	����Buffer
	DWORD*	mPixelBuffer;

	///	���ڿ��
	DWORD	mWindowWidth;

	///	���ڸ߶�
	DWORD	mWindowHeight;

	///	�����豸�������
	HDC		mHDC;

	///	���ڼ����豸�������
	HDC		mCDC;

	/// ��Ⱦλͼ���
	HBITMAP mRenderBitMap;

	///	���ھ��
	HWND	mHWND;

};


#endif
