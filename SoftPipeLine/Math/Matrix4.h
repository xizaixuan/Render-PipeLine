/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   矩阵类
/// \author  zhangxuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Matrix4_H_
#define _Matrix4_H_

class Matrix4
{
public:
	/// \brief 默认构造函数
	Matrix4(void);

	/// \brief 带参数构造函数
	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	/// \brief 析构函数
	~Matrix4(void);

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Matrix4& operator =(const Matrix4& a);

	/// \brief 重载二元"+"运算符
	Matrix4 operator +(const Matrix4& a) const;

	/// \brief 重载二元"*"运算符
	Matrix4 operator *(const Matrix4& a) const;

public:
	/// \brief 置为单位矩阵
	void identity();

	/// \brief 初始化
	void init(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	/// \brief  计算逆矩阵
	Matrix4 inverse();

public:

	///	数据分量
	union
	{
		float M[4][4]; 

		struct
		{
			float M00, M01, M02, M03;
			float M10, M11, M12, M13;
			float M20, M21, M22, M23;
			float M30, M31, M32, M33;
		}; 
	};
};

#endif
