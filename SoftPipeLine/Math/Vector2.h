/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ��ά����
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Vector2_H_
#define _Vector2_H_

class Vector2
{
public:
	/// \brief �������캯��
	Vector2(float x, float y);

	/// \brief ���ƹ��캯��
	Vector2(const Vector2& a);

	/// \brief ��������
	~Vector2();

	/// \brief ���ظ�ֵ�����,���������ã���ʵ����ֵ
	Vector2& operator= (const Vector2& a);

	/// \brief ���ض�Ԫ"+"�����
	Vector2 operator+ (const Vector2& a) const;

	/// \brief ���ض�Ԫ"-"�����
	Vector2 operator- (const Vector2& a) const;

	/// \brief ���ض�Ԫ"*"����� �����
	Vector2 operator* (float a) const;

	/// \brief ���ض�Ԫ"*"����� ������
	float operator* (const Vector2& a) const;

public:
	///	���ݷ���
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


