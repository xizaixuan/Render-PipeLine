/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   数学常量及算法
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _MathUtil_H_
#define _MathUtil_H_

#include <math.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

const float epsilon_e4 = (float)(1E-4);
const float epsilon_e5 = (float)(1E-5);
const float epsilon_e6 = (float)(1E-6);

const float PI = ((float)3.141592654f);

float AngelToRadian(float ang);

float RadianToAngel(float rads);

/// brief 求向量长度
float Length(const Vector2& v);
float Length(const Vector3& v);
float Length(const Vector4& v);

/// brief 求两向量的叉积
Vector2 Normalize(Vector2& v);
Vector3 Normalize(Vector3& v);
Vector4 Normalize(Vector4& v);

/// brief 求两向量的叉积
Vector2 Cross(const Vector2& a, const Vector2& b);
Vector3 Cross(const Vector3& a, const Vector3& b);
Vector4 Cross(const Vector4& a, const Vector4& b);

/// brief 设置为零向量
template<typename T>
T Zero(T& v);

#endif
