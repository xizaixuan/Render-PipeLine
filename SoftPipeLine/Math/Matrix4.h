/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ������
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Matrix4_H_
#define _Matrix4_H_

#include "Vector3.h"

class Matrix4
{
public:
	/// \brief Ĭ�Ϲ��캯��
	Matrix4(void);

	/// \brief ���������캯��
	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	/// \brief ��������
	~Matrix4(void);

	/// \brief ���ظ�ֵ�����,���������ã���ʵ����ֵ
	Matrix4& operator =(const Matrix4& a);

	/// \brief ���ض�Ԫ"+"�����
	Matrix4 operator +(const Matrix4& a) const;

	/// \brief ���ض�Ԫ"*"�����
	Matrix4 operator *(const Matrix4& a) const;

public:
	/// \brief ��Ϊ��λ����
	void identity();

	/// \brief ��ʼ��
	void init(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	/// \brief  ���������
	Matrix4 inverse();

	/// \brief ����λ����Ϣ
	void setTranslate(float x, float y, float z);
	void setTranslate(Vector3 pos);

public:

	///	���ݷ���
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
