/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   窗口管理类
/// \author  zhangxuan
/// \date    2017-05
/////////////////////////////////////////////////////////////////////////////////
#ifndef WinApp_H_
#define WinApp_H_

#include <windows.h>
#include "../Util/Singleton.h"

class WinApp : public Singleton<WinApp>
{
	SINGLETON_DEFINE(WinApp)
private:
	WinApp(void);
	~WinApp(void);

public:
	/// \brief 创建窗口
	void	create(HINSTANCE hInstance, int nCmdShow, int width, int height, LPSTR caption);	

	/// \brief 获取窗口的宽
	int		getWidth();

	/// \brief 获取窗口的长
	int		getHeight();

	/// \brief 获取窗口句柄
	HWND	getHwnd();

private:
	/// \brief 窗口注册
	WORD	registerClass(HINSTANCE hInstance);

	/// \brief 初始化
	bool	init(HINSTANCE hInstance, int nCmdShow);

	/// \brief 消息回调函数
	static	LRESULT CALLBACK  wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	///	窗口名称
	LPSTR	mCaption;

	///	窗口长度
	int		mHeight;

	///	窗口宽度
	int		mWidth;

	///	窗口句柄
	HWND	mHWND;
};

#endif