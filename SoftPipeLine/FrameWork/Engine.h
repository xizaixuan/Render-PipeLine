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
#include "../Math/Vector2.h"

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

	/// \brief ���press�¼�
	void OnMouseDown(WPARAM btnState, int x, int y);

	/// \brief ���release�¼�
	void OnMouseUp(WPARAM btnState, int x, int y);

	/// \brief ���move�¼�
	void OnMouseMove(WPARAM btnState, int x, int y);

private:
	/// \brief ������ݸ���
	void updateCamera(float dt);

private:
	/// \brief �����
	Camera* mCamera;

	/// �������
	Vector2 mLastMousePos;

	float mRadius;
	float mPhi;
	float mTheta;
};


#endif