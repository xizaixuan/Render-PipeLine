#include "Vector2.h"
#include "MathUtil.h"

Vector2::Vector2()
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


void Vector2::zero()
{
	x = y = 0.0f;
}

void Vector2::init(float x, float y)
{
	this->x = x;
	this->y = y;
}


void Vector2::normalize()
{
	//计算模的长度
	float length = sqrtf(x*x + y*y);

	//检查除零
	if (length > epsilon_e5)
	{
		float lengthInv = 1.0f/length;

		x = x*lengthInv;
		y = y*lengthInv;
	}
}