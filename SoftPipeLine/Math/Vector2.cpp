#include "Vector2.h"
#include "MathUtil.h"

Vector2::Vector2()
	: x(0.0f)
	, y(0.0f)
{
}

Vector2::Vector2(float tx, float ty)
	:x(tx)
	,y(ty)
{
}

Vector2::Vector2(const Vector2& a)
	:x(a.x)
	,y(a.y)
{
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator = (const Vector2& a)
{
	x = a.x;
	y = a.y;

	return *this;
}

Vector2 Vector2::operator +(const Vector2& a) const
{
	return Vector2( x+a.x , y+a.y );
}

Vector2 Vector2::operator -(const Vector2& a) const
{
	return Vector2( x-a.x , y-a.y );
}

Vector2 Vector2::operator *(float a) const
{
	return Vector2(x*a,y*a);
}

float Vector2::operator *(const Vector2& a) const
{
	return x*a.x+y*a.y;
}