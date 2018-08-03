/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   三维向量
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Float3_H_
#define _Float3_H_

#define  float3 Float3

class Float3
{
public:
	/// \brief 参数构造函数
	Float3(float x, float y, float z);

	/// \brief 复制构造函数
	Float3(const Float3& a);

	/// \brief 析构函数
	~Float3();

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Float3& operator =(const Float3& a);

	/// \brief 重载二元"+"运算符
	Float3 operator +(const Float3& a) const;

	/// \brief 重载二元"-"运算符
	Float3 operator -(const Float3& a) const;

	/// \brief 重载二元"*"运算符 与标量
	Float3 operator *(float a) const;

	/// \brief 重载二元"*"运算符 与向量
	float operator *(const Float3& a) const;

public:
	float x;
	float y;
	float z;
};

#endif