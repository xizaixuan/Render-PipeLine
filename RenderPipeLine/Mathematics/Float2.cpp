#include "Float2.h"

Float2::Float2(float _x, float _y)
	:x(_x)
	,y(_y)
{
}

Float2::Float2(const Float2& a)
	:x(a.x)
	,y(a.y)
{
}

Float2::~Float2()
{
}

Float2& Float2::operator = (const Float2& a)
{
	x = a.x;
	y = a.y;

	return *this;
}

Float2 Float2::operator +(const Float2& a) const
{
	return Float2( x+a.x , y+a.y );
}

Float2 Float2::operator -(const Float2& a) const
{
	return Float2( x-a.x , y-a.y );
}

Float2 Float2::operator *(float a) const
{
	return Float2(x*a, y*a);
}

float Float2::operator *(const Float2& a) const
{
	return x*a.x + y*a.y;
}