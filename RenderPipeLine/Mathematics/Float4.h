/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ��ά����
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
	/// \brief �������캯��
	Float4(float x, float y, float z, float w);
	Float4(const Float3& value, float w);

	/// \brief ���ƹ��캯��
	Float4(const Float4& a);

	/// \brief ��������
	~Float4();

	/// \brief ���ظ�ֵ�����,���������ã���ʵ����ֵ
	Float4& operator = (const Float4& a);

	/// \brief ���ض�Ԫ"+"�����
	Float4 operator +(const Float4& a) const;
	Float4 operator +=(const Float4& a);

	/// \brief ���ض�Ԫ"-"�����
	Float4 operator -(const Float4& a) const;
	Float4 operator -=(const Float4& a);

	/// \brief ���ض�Ԫ"*"����� �����
	Float4 operator *(float a) const;
	Float4 operator *(const Matrix& a) const;

public:
	float x;
	float y;
	float z;
	float w;
};

#endif
