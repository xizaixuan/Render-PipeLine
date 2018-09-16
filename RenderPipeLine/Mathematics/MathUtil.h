/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ��ѧ�������㷨
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _MathUtil_H_
#define _MathUtil_H_

#include <math.h>
#include "float2.h"
#include "float3.h"
#include "float4.h"
#include "Matrix.h"
#include <limits>
#include "Int2.h"

namespace MathUtil
{
	const float epsilon = std::numeric_limits<float>::epsilon();
	const float pi = 3.141592654f;

	float AngelToRadian(float ang);
	float RadianToAngel(float rads);

	/// brief ����������
	float Length(const float2& v);
	float Length(const float3& v);
	float Length(const float4& v);
	float Length(const int2& v);

	/// brief ��λ��
	float2 Normalize(float2& v);
	float3 Normalize(float3& v);
	float4 Normalize(float4& v);

	/// brief ���������Ĳ��
	float2 Cross(const float2& a, const float2& b);
	float3 Cross(const float3& a, const float3& b);

	float4 Homogenous(float4& value);

	/// brief �Ƚ��������Ƿ����
	bool IsEqual(float a, float b);
	bool IsEqual(int a, int b);

	Matrix Inverse(Matrix mat);

	template<typename T>
	static T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : (x > high ? high : x);
	}

	template<typename T>
	static T Lerp(const T& a, const T& b, const float factor)
	{
		return a + (b-a)*factor;
	}

	float3 Forward(Matrix mat);
	float3 Up(Matrix mat);
	float3 Right(Matrix mat);
	float3 Position(Matrix mat);
}

#endif
