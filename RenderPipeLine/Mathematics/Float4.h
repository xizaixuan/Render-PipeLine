/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   四维向量
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Float4_H_
#define _Float4_H_

#define  float4 Float4

class Float4
{
public:
	/// \brief 参数构造函数
	Float4(float x, float y, float z);

	/// \brief 参数构造函数
	Float4(float x, float y, float z, float w);

	/// \brief 复制构造函数
	Float4(const Float4& a);

	/// \brief 析构函数
	~Float4();

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Float4& operator = (const Float4& a);

	/// \brief 重载二元"+"运算符
	Float4 operator +(const Float4& a) const;

	/// \brief 重载二元"-"运算符
	Float4 operator -(const Float4& a) const;

	/// \brief 重载二元"*"运算符 与标量
	Float4 operator *(float a) const;

	/// \brief 重载二元"*"运算符 与向量
	float operator *(const Float4& a) const;

public:
	float x;
	float y;
	float z;
	float w;
};

#endif
