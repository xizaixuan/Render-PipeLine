#include "Float4.h"

Float4::Float4(float _x, float _y, float _z)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(1.0f)
{
}

Float4::Float4(float _x, float _y, float _z, float _w)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{}

Float4::Float4(const Float4& a)
	: x(a.x)
	, y(a.y)
	, z(a.z)
	, w(a.w)
{
}

Float4::~Float4()
{
}

Float4& Float4::operator = (const Float4& a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;

	return *this;
}

Float4 Float4::operator +(const Float4& a) const
{
	return Float4( x+a.x, y+a.y, z+a.z );
}

Float4 Float4::operator -(const Float4& a) const
{
	return Float4( x-a.x, y-a.y, z-a.z );
}

Float4 Float4::operator *(float a) const
{
	return Float4( x*a, y*a, z*a, w*a);
}

float Float4::operator *(const Float4& a) const
{
	return( (x * a.x) + (y * a.y) + (z * a.z) );
}