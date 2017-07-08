/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ���
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../Math/MathUtil.h"

class Camera
{
public:
	/// \brief ���캯��
	Camera();

	/// \brief ��������
	~Camera();

	/// \brief ����͸�Ӳ���
	void update(float fov, float aspect, float znear, float zfar);

	/// \brief �������λ�ü��۲�Ŀ��λ��
	void update(Vector3 position, Vector3 target);

	/// \brief �����Ӿ���
	void buildViewMatrix();

	/// \brief ����͸�Ӿ���
	void buildPerspectiveMatrix();


	/// \brief ��ȡ�Ӿ���
	Matrix4 GetViewMatrix();

	/// \brief ��ȡ͸�Ӿ���
	Matrix4 GetPerspectiveMatrix();

	public:
	///	��Ұ
	float mFov;

	///	��߱�
	float mAspect;

	///	���ü���
	float mZNear;

	///	Զ�ü���
	float mZFar;

	///	���λ��
	Vector3 mPosition;

	///	�۲�Ŀ��λ��
	Vector3 mTarget;

	///	��ǰ����
	Vector3 mForward;

	///	��������
	Vector3 mUp;

	///	��������
	Vector3 mRight;

	///	�Ӿ���
	Matrix4 mView;

	///	͸�Ӿ���
	Matrix4 mProj;
};

#endif