/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   ���ڹ�����
/// \author  xizaixuan
/// \date    2017-07
/////////////////////////////////////////////////////////////////////////////////
#ifndef WinApp_H_
#define WinApp_H_

#include <windows.h>
#include "..\Utility\Singleton.h"

class WinApp : public Singleton<WinApp>
{
	SINGLETON_DEFINE(WinApp)
private:
	WinApp();
	~WinApp();

public:
	/// \brief ��������
	void	create(HINSTANCE hInstance, int nCmdShow, int width, int height, LPSTR caption);	

	/// \brief ��ȡ���ڵĿ�
	int		getWidth();

	/// \brief ��ȡ���ڵĳ�
	int		getHeight();

	/// \brief ��ȡ���ھ��
	HWND	getHwnd();

private:
	/// \brief ����ע��
	WORD	registerClass(HINSTANCE hInstance);

	/// \brief ��ʼ��
	bool	init(HINSTANCE hInstance, int nCmdShow);

	/// \brief ��Ϣ�ص�����
	static	LRESULT CALLBACK  wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	///	��������
	LPSTR	mCaption;

	///	���ڸ߶�
	int		mHeight;

	///	���ڿ��
	int		mWidth;

	///	���ھ��
	HWND	mHWND;
};

#endif