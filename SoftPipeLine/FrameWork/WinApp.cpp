#include "WinApp.h"


WinApp::WinApp(void)
{
}


WinApp::~WinApp(void)
{
}


void WinApp::create(HINSTANCE hInstance, int nCmdShow, int width, int height, LPSTR caption)
{
	mWidth		= width ;
	mHeight		= height ;
	mCaption	= caption;

	registerClass(hInstance);

	init(hInstance,nCmdShow);
}


int	WinApp::getWidth()
{
	return mWidth;
}


int	WinApp::getHeight()
{
	return mHeight;
}


HWND WinApp::getHwnd()
{
	return mHWND;
}


WORD WinApp::registerClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WinApp::wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= mCaption;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}


bool WinApp::init(HINSTANCE hInstance, int nCmdShow)
{
	mHWND = CreateWindow(
		mCaption, 
		mCaption, 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		0, 
		mWidth,
		mHeight, 
		NULL, 
		NULL, 
		hInstance, 
		NULL);

	if (!mHWND)
		return false;

	ShowWindow(mHWND, nCmdShow);

	return true;
}


LRESULT CALLBACK  WinApp::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


