/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   窗口管理类
/// \author  xizaixuan
/// \date    2017-07
/////////////////////////////////////////////////////////////////////////////////
#ifndef WinApp_H_
#define WinApp_H_

#include <windows.h>
#include "..\Utility\Singleton.h"
#include <winuser.h>

class WinApp : public Singleton<WinApp>
{
	SINGLETON_DEFINE(WinApp)
private:
	WinApp();
	~WinApp();

public:
	/// \brief 创建窗口
	void	Create(HINSTANCE hInstance, int nCmdShow, int width, int height, LPSTR caption);

	/// \brief 获取窗口的宽
	int		GetWidth();

	/// \brief 获取窗口的长
	int		GetHeight();

	/// \brief 获取窗口句柄
	HWND	GetHwnd();

private:
	/// \brief 窗口注册
	WORD	RegisterClass(HINSTANCE hInstance);

	/// \brief 初始化
	bool	Init(HINSTANCE hInstance, int nCmdShow);

	///	窗口名称
	LPSTR	m_Caption;

	///	窗口高度
	int		m_Height;

	///	窗口宽度
	int		m_Width;

	///	窗口句柄
	HWND	m_HWND;
};

#endif