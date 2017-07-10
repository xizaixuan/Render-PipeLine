/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   N维向量，向量的基类
/// \author  xizaixuan
/// \date    2017-05
/////////////////////////////////////////////////////////////////////////////////
#ifndef Engine_H_
#define Engine_H_

#include <Windows.h>
#include "../Util/Singleton.h"
#include "../Math/Vector2.h"

class Camera;

class Engine : public Singleton<Engine>
{
	SINGLETON_DEFINE(Engine)
private:
	Engine();
	~Engine();

public:
	/// \brief 初始化
	void init(HINSTANCE hInstance, int nCmdShow);

	/// \brief 资源销毁
	void destroy();

	/// \brief 更新
	void update(float dt);

	/// \brief 鼠标press事件
	void OnMouseDown(WPARAM btnState, int x, int y);

	/// \brief 鼠标release事件
	void OnMouseUp(WPARAM btnState, int x, int y);

	/// \brief 鼠标move事件
	void OnMouseMove(WPARAM btnState, int x, int y);

private:
	/// \brief 相机数据更新
	void updateCamera(float dt);

private:
	/// \brief 主相机
	Camera* mCamera;

	/// 鼠标坐标
	Vector2 mLastMousePos;

	float mRadius;
	float mPhi;
	float mTheta;
};


#endif