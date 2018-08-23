/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ���
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "..\Mathematics\Float3.h"
#include "..\Mathematics\Matrix.h"

class Camera
{
public:
	/// \brief ���캯��
	Camera();

	/// \brief ��������
	~Camera();

	/// \brief ����͸�Ӳ���
	void SetParams(float fov, float aspect, float znear, float zfar);

	/// \brief �������λ�ü��۲�Ŀ��λ��
	void SetParams(float3 position, float3 target);

	/// \brief �����Ӿ���
	void BuildViewMatrix();

	/// \brief ����͸�Ӿ���
	void BuildPerspectiveMatrix();

	/// \brief ��ȡ�Ӿ���
	Matrix GetViewMatrix();

	/// \brief ��ȡ͸�Ӿ���
	Matrix GetPerspectiveMatrix();

	public:
	///	��Ұ
	float m_Fov;

	///	��߱�
	float m_Aspect;

	///	���ü���
	float m_ZNear;

	///	Զ�ü���
	float m_ZFar;

	///	���λ��
	float3 m_Position;

	///	�۲�Ŀ��λ��
	float3 m_Target;

	///	��ǰ����
	float3 m_Forward;

	///	��������
	float3 m_Up;

	///	��������
	float3 m_Right;

	///	�Ӿ���
	Matrix m_View;

	///	͸�Ӿ���
	Matrix m_Proj;
};

#endif