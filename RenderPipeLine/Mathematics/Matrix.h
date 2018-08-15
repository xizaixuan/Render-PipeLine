/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   矩阵
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Matrix_H_
#define _Matrix_H_

#include "Float4.h"

class Matrix
{
public:
	/// \brief 默认构造函数
	Matrix(void);

	/// \brief 带参数构造函数
	Matrix(float4 row0, float4 row1, float4 row2, float4 row3);

	/// \brief 析构函数
	~Matrix(void);

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Matrix& operator =(const Matrix& a);

	/// \brief 重载二元"*"运算符
	Matrix operator *(const float4& a) const;
	Matrix operator *(const Matrix& a) const;

public:
	/// \brief 置为单位矩阵
	void identity();

	/// \brief 设置参数
	void set(float4 row0, float4 row1, float4 row2, float4 row3);

public:
	float4 r0;
	float4 r1;
	float4 r2;
	float4 r3;
};

#endif
