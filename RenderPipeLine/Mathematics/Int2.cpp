#include "Int2.h"

Int2::Int2(int _x, int _y)
	:x(_x)
	,y(_y)
{
}

Int2::Int2(const Int2& a)
	:x(a.x)
	,y(a.y)
{
}

Int2::~Int2()
{
}

Int2& Int2::operator = (const Int2& a)
{
	x = a.x;
	y = a.y;

	return *this;
}

Int2 Int2::operator +(const Int2& a) const
{
	return Int2( x+a.x , y+a.y );
}

Int2 Int2::operator -(const Int2& a) const
{
	return Int2( x-a.x , y-a.y );
}