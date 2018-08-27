#include "Float4.h"
#include "Matrix.h"

Float4::Float4(float _x, float _y, float _z, float _w)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{}

Float4::Float4(const Float3& value, float w)
	: x(value.x)
	, y(value.y)
	, z(value.z)
	, w(w)
{
}

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

Float4 Float4::operator *(float a) const
{
	return Float4( x*a, y*a, z*a, w*a);
}

Float4 Float4::operator *(const Matrix & a) const
{
	return Float4(
		x * a.r0.x + y * a.r1.x + z * a.r2.x + w * a.r3.x,
		x * a.r0.y + y * a.r1.y + z * a.r2.y + w * a.r3.y,
		x * a.r0.z + y * a.r1.z + z * a.r2.z + w * a.r3.z,
		x * a.r0.w + y * a.r1.w + z * a.r2.w + w * a.r3.w);
}
