#include "Vector3.h"

#include "MathUtil.h"


Vector3::Vector3()
{
}


Vector3::Vector3(float tx, float ty, float tz)
	: x(tx)
	, y(ty)
	, z(tz)
{
}


Vector3::Vector3(const Vector3& a)
	: x(a.x)
	, y(a.y)
	, z(a.z)
{
}

Vector3::~Vector3()
{
}


Vector3& Vector3::operator =(const Vector3& a)
{
	x = a.x;
	y = a.y;
	z = a.z;

	return *this;
}


Vector3 Vector3::operator +(const Vector3& a) const
{
	return Vector3( x+a.x, y+a.y, z+a.z );
}


Vector3 Vector3::operator -(const Vector3& a) const
{
	return Vector3( x-a.x, y-a.y, z-a.z );
}


Vector3 Vector3::operator *(float a) const
{
	return Vector3( x*a, y*a, z*a );
}


float Vector3::operator *(const Vector3& a) const
{
	return x*a.x + y*a.y + z*a.z;
}


void Vector3::zero()
{
	x = y = z = 0.0f;
}


void Vector3::init(float x,float y,float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


void Vector3::normalize()
{
	// 计算向量模
	float length = sqrtf(x*x + y*y + z*z);

	// 检查除零
	if (length > epsilon_e5) 
	{
		float lengthInv = 1.0f/length;

		x*=lengthInv;
		y*=lengthInv;
		z*=lengthInv;
	}
}