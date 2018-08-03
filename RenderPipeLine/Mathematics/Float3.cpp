#include "Float3.h"

Float3::Float3(float _x, float _y, float _z)
	: x(_x)
	, y(_y)
	, z(_z)
{
}

Float3::Float3(const Float3& a)
	: x(a.x)
	, y(a.y)
	, z(a.z)
{
}

Float3::~Float3()
{
}

Float3& Float3::operator =(const Float3& a)
{
	x = a.x;
	y = a.y;
	z = a.z;

	return *this;
}

Float3 Float3::operator +(const Float3& a) const
{
	return Float3( x+a.x, y+a.y, z+a.z );
}

Float3 Float3::operator -(const Float3& a) const
{
	return Float3( x-a.x, y-a.y, z-a.z );
}

Float3 Float3::operator *(float a) const
{
	return Float3( x*a, y*a, z*a );
}

float Float3::operator *(const Float3& a) const
{
	return x*a.x + y*a.y + z*a.z;
}