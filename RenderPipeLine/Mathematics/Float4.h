/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   四维向量
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Float4_H_
#define _Float4_H_

#include "Float3.h"

#define  float4 Float4
struct Matrix;

struct Float4
{
public:
	/// \brief 参数构造函数
	Float4(float x, float y, float z, float w);
	Float4(const Float3& value, float w);

	/// \brief 复制构造函数
	Float4(const Float4& a);

	/// \brief 析构函数
	~Float4();

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Float4& operator = (const Float4& a);

	/// \brief 重载二元"+"运算符
	Float4 operator +(const Float4& a) const;
	Float4 operator +=(const Float4& a);

	/// \brief 重载二元"-"运算符
	Float4 operator -(const Float4& a) const;
	Float4 operator -=(const Float4& a);

	/// \brief 重载二元"*"运算符 与标量
	Float4 operator *(float a) const;
	Float4 operator *(const Matrix& a) const;

public:
	float x;
	float y;
	float z;
	float w;
};

#endif
