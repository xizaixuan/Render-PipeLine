#include "Vector4.h"

#include "MathUtil.h"

Vector4::Vector4(float tx, float ty, float tz)
	: x(tx)
	, y(ty)
	, z(tz)
	, w(1.0f)
{
}

Vector4::Vector4(float tx, float ty, float tz, float tw)
	: x(tx)
	, y(ty)
	, z(tz)
	, w(tw)
{}

Vector4::Vector4(const Vector4& a)
	: x(a.x)
	, y(a.y)
	, z(a.z)
	, w(a.w)
{
}

Vector4::~Vector4()
{
}

Vector4& Vector4::operator = (const Vector4& a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;

	return *this;
}

Vector4 Vector4::operator +(const Vector4& a) const
{
	return Vector4( x+a.x, y+a.y, z+a.z );
}

Vector4 Vector4::operator -(const Vector4& a) const
{
	return Vector4( x-a.x, y-a.y, z-a.z );
}

Vector4 Vector4::operator *(float a) const
{
	return Vector4( x*a, y*a, z*a );
}

float Vector4::operator *(const Vector4& a) const
{
	return( (x * a.x) + (y * a.y) + (z * a.z) );
}

Vector4 Vector4::operator *(const Matrix4& a) const
{
	Vector4 result(0.0f, 0.0f, 0.0f, 0.0f);

	result.x = x * a.M[0][0] + y * a.M[1][0] + z * a.M[2][0] + w * a.M[3][0];
	result.y = x * a.M[0][1] + y * a.M[1][1] + z * a.M[2][1] + w * a.M[3][1];
	result.z = x * a.M[0][2] + y * a.M[1][2] + z * a.M[2][2] + w * a.M[3][2];
	result.w = x * a.M[0][3] + y * a.M[1][3] + z * a.M[2][3] + w * a.M[3][3];

	return result;

}

void Vector4::homogenous()
{
	this->x /= w;
	this->y /= w;
	this->z /= w;
	this->w /= w;
}