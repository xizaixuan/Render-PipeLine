/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   四维向量
/// \author  zhangxuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Vector4_H_
#define _Vector4_H_

class Vector3;
class Matrix4;

class Vector4
{
public:
	/// \brief 默认构造函数
	Vector4();

	/// \brief 参数构造函数
	Vector4(float x, float y, float z);

	/// \brief 参数构造函数
	Vector4(float x, float y, float z, float w);

	/// \brief 复制构造函数
	Vector4(const Vector4& a);

	/// \brief 析构函数
	~Vector4();

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Vector4& operator = (const Vector4& a);

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Vector4& operator = (const Vector3& a);

	/// \brief 重载二元"+"运算符
	Vector4 operator +(const Vector4& a) const;

	/// \brief 重载二元"-"运算符
	Vector4 operator -(const Vector4& a) const;

	/// \brief 重载二元"*"运算符 与标量
	Vector4 operator *(float a) const;

	/// \brief 重载二元"*"运算符 与向量
	float operator *(const Vector4& a) const;

	/// \brief 重载二元"*"运算符 与向量
	Vector4 operator *(const Matrix4& a) const;

public:
	/// \brief 置为零向量
	void zero();

	/// \brief 初始化
	void init(float x,float y,float z);

	/// \brief 初始化
	void init(float x,float y,float z,float w);

	/// \brief 向量标准化
	void normalize();

	/// \brief 标准齐次空间变换
	void Homogenous();

public:
	union
	{
		float M[4]; 
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};

#endif
