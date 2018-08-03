/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   二维向量
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Float2_H_
#define _Float2_H_

#define  float2 Float2

class Float2
{
public:
	/// \brief 参数构造函数
	Float2(float x, float y);

	/// \brief 复制构造函数
	Float2(const Float2& a);

	/// \brief 析构函数
	~Float2();

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Float2& operator= (const Float2& a);

	/// \brief 重载二元"+"运算符
	Float2 operator+ (const Float2& a) const;

	/// \brief 重载二元"-"运算符
	Float2 operator- (const Float2& a) const;

	/// \brief 重载二元"*"运算符 与标量
	Float2 operator* (float a) const;

	/// \brief 重载二元"*"运算符 与向量
	float operator* (const Float2& a) const;

public:
	float x;
	float y;
};

#endif


