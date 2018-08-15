/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ����
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Matrix_H_
#define _Matrix_H_

#include "Float4.h"

class Matrix
{
public:
	/// \brief Ĭ�Ϲ��캯��
	Matrix(void);

	/// \brief ���������캯��
	Matrix(float4 row0, float4 row1, float4 row2, float4 row3);

	/// \brief ��������
	~Matrix(void);

	/// \brief ���ظ�ֵ�����,���������ã���ʵ����ֵ
	Matrix& operator =(const Matrix& a);

	/// \brief ���ض�Ԫ"*"�����
	Matrix operator *(const float4& a) const;
	Matrix operator *(const Matrix& a) const;

public:
	/// \brief ��Ϊ��λ����
	void identity();

	/// \brief ���ò���
	void set(float4 row0, float4 row1, float4 row2, float4 row3);

public:
	float4 r0;
	float4 r1;
	float4 r2;
	float4 r3;
};

#endif
