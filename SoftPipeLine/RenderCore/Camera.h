/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   相机
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../Math/MathUtil.h"

class Camera
{
public:
	/// \brief 构造函数
	Camera();

	/// \brief 析构函数
	~Camera();

	/// \brief 更新透视参数
	void update(float fov, float aspect, float znear, float zfar);

	/// \brief 更新相机位置及观察目标位置
	void update(Vector3 position, Vector3 target);

	/// \brief 建立视矩阵
	void buildViewMatrix();

	/// \brief 建立透视矩阵
	void buildPerspectiveMatrix();

private:
	///	视野
	float mFov;

	///	宽高比
	float mAspect;

	///	近裁剪面
	float mZNear;

	///	远裁剪面
	float mZFar;

	///	相机位置
	Vector3 mPosition;

	///	观察目标位置
	Vector3 mTarget;

	///	向前向量
	Vector3 mForward;

	///	向上向量
	Vector3 mUp;

	///	向左向量
	Vector3 mRight;

	///	视矩阵
	Matrix4 mView;

	///	视逆矩阵
	Matrix4 mInvView;

	///	透视矩阵
	Matrix4 mProj;

	///	透视逆矩阵
	Matrix4 mInvProj;

	///	视空间到透视空间变换矩阵
	Matrix4 mViewProj;

	///	视空间到透视空间变换逆矩阵
	Matrix4 mInvViewProj;
};

#endif