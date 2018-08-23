/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   相机
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
	/// \brief 构造函数
	Camera();

	/// \brief 析构函数
	~Camera();

	/// \brief 设置透视参数
	void SetParams(float fov, float aspect, float znear, float zfar);

	/// \brief 设置相机位置及观察目标位置
	void SetParams(float3 position, float3 target);

	/// \brief 建立视矩阵
	void BuildViewMatrix();

	/// \brief 建立透视矩阵
	void BuildPerspectiveMatrix();

	/// \brief 获取视矩阵
	Matrix GetViewMatrix();

	/// \brief 获取透视矩阵
	Matrix GetPerspectiveMatrix();

	public:
	///	视野
	float m_Fov;

	///	宽高比
	float m_Aspect;

	///	近裁剪面
	float m_ZNear;

	///	远裁剪面
	float m_ZFar;

	///	相机位置
	float3 m_Position;

	///	观察目标位置
	float3 m_Target;

	///	向前向量
	float3 m_Forward;

	///	向上向量
	float3 m_Up;

	///	向左向量
	float3 m_Right;

	///	视矩阵
	Matrix m_View;

	///	透视矩阵
	Matrix m_Proj;
};

#endif