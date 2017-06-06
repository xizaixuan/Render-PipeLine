/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   ��ά����
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Vector3_H_
#define _Vector3_H_

class Vector3
{
public:
	/// \brief Ĭ�Ϲ��캯��
	Vector3();

	/// \brief �������캯��
	Vector3(float x, float y, float z);

	/// \brief ���ƹ��캯��
	Vector3(const Vector3& a);

	/// \brief ��������
	~Vector3();

	/// \brief ���ظ�ֵ�����,���������ã���ʵ����ֵ
	Vector3& operator =(const Vector3& a);

	/// \brief ���ض�Ԫ"+"�����
	Vector3 operator +(const Vector3& a) const;

	/// \brief ���ض�Ԫ"-"�����
	Vector3 operator -(const Vector3& a) const;

	/// \brief ���ض�Ԫ"*"����� �����
	Vector3 operator *(float a) const;

	/// \brief ���ض�Ԫ"*"����� ������
	float operator *(const Vector3& a) const;

public:
	///	���ݷ���
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