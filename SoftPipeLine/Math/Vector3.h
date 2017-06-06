/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   三维向量
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Vector3_H_
#define _Vector3_H_

class Vector3
{
public:
	/// \brief 默认构造函数
	Vector3();

	/// \brief 参数构造函数
	Vector3(float x, float y, float z);

	/// \brief 复制构造函数
	Vector3(const Vector3& a);

	/// \brief 析构函数
	~Vector3();

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Vector3& operator =(const Vector3& a);

	/// \brief 重载二元"+"运算符
	Vector3 operator +(const Vector3& a) const;

	/// \brief 重载二元"-"运算符
	Vector3 operator -(const Vector3& a) const;

	/// \brief 重载二元"*"运算符 与标量
	Vector3 operator *(float a) const;

	/// \brief 重载二元"*"运算符 与向量
	float operator *(const Vector3& a) const;

public:
	///	数据分量
	union
	{
		float M[3];
		struct
		{
			float x;
			float y;
			float z;
		};
	};
};

#endif