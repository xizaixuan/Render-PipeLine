/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   Nά�����������Ļ���
/// \author  xizaixuan
/// \date    2017-05
/////////////////////////////////////////////////////////////////////////////////
#ifndef Engine_H_
#define Engine_H_

#include <Windows.h>
#include "../Util/Singleton.h"

class Camera;

class Engine : public Singleton<Engine>
{
	SINGLETON_DEFINE(Engine)
private:
	Engine();
	~Engine();

public:
	/// \brief ��ʼ��
	void init(HINSTANCE hInstance, int nCmdShow);

	/// \brief ��Դ����
	void destroy();

	/// \brief ����
	void update(float dt);

private:
	/// \brief ������ݸ���
	void updateCamera(float dt);

private:
	/// \brief �����
	Camera* mCamera;
};


#endif