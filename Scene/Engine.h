/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   引擎控制类
/// \author  xizaixuan
/// \date    2017-07
/////////////////////////////////////////////////////////////////////////////////
#ifndef Engine_H_
#define Engine_H_

#include <Windows.h>
#include "..\RenderPipeLine\Utility\Singleton.h"
#include "..\RenderPipeLine\Mathematics\Float2.h"
#include "..\RenderPipeLine\Utility\RenderBuffer.h"

class Camera;

class Engine : public Singleton<Engine>
{
	SINGLETON_DEFINE(Engine)
private:
	Engine();
	~Engine();

public:
	/// \brief 初始化
	void Init(HINSTANCE hInstance, int nCmdShow, int width, int height);

	/// \brief 资源销毁
	void Destroy();

	/// \brief 更新
	void Update(float dt);

	/// \brief 渲染场景
	void RenderScene();

	void OnMouseMove(WPARAM btnState, int x, int y);

private:
	Camera* m_pCamera;

	float m_Theta;
	float m_Phi;
	float m_Radius;

	float2 m_LastMousePos;

	vector<RenderBuffer> m_RenderBuffers;
};

#endif