/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   二维向量
/// \author  zhangxuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Vector2_H_
#define _Vector2_H_

class Vector2
{
public:
	/// \brief 默认构造函数
	Vector2();

	/// \brief 参数构造函数
	Vector2(float x, float y);

	/// \brief 复制构造函数
	Vector2(const Vector2& a);

	/// \brief 析构函数
	~Vector2();

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Vector2& operator= (const Vector2& a);

	/// \brief 重载二元"+"运算符
	Vector2 operator+ (const Vector2& a) const;

	/// \brief 重载二元"-"运算符
	Vector2 operator- (const Vector2& a) const;

	/// \brief 重载二元"*"运算符 与标量
	Vector2 operator* (float a) const;

	/// \brief 重载二元"*"运算符 与向量
	float operator* (const Vector2& a) const;

public:
	/// \brief 置为零向量
	void zero();

	/// \brief 初始化
	void init(float x, float y);

	/// \brief 向量标准化
	void normalize();

public:
	///	数据分量
	union
	{
		float M[2];
		struct
		{
			float x;
			float y;
		};
	};
};

#endif


