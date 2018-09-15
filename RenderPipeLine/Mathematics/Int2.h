/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ��ά��
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Int2_H_
#define _Int2_H_

#define  int2 Int2

struct Int2
{
public:
	/// \brief �������캯��
	Int2(int x, int y);

	/// \brief ���ƹ��캯��
	Int2(const Int2& a);

	/// \brief ��������
	~Int2();

	/// \brief ���ظ�ֵ�����,���������ã���ʵ����ֵ
	Int2& operator= (const Int2& a);

	/// \brief ���ض�Ԫ"+"�����
	Int2 operator+ (const Int2& a) const;

	/// \brief ���ض�Ԫ"-"�����
	Int2 operator- (const Int2& a) const;

public:
	int x;
	int y;
};

#endif


