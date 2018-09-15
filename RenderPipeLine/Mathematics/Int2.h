/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   二维点
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef _Int2_H_
#define _Int2_H_

#define  int2 Int2

struct Int2
{
public:
	/// \brief 参数构造函数
	Int2(int x, int y);

	/// \brief 复制构造函数
	Int2(const Int2& a);

	/// \brief 析构函数
	~Int2();

	/// \brief 重载赋值运算符,并返回引用，以实现左值
	Int2& operator= (const Int2& a);

	/// \brief 重载二元"+"运算符
	Int2 operator+ (const Int2& a) const;

	/// \brief 重载二元"-"运算符
	Int2 operator- (const Int2& a) const;

public:
	int x;
	int y;
};

#endif


