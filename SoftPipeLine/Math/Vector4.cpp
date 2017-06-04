#include "Vector4.h"

#include "MathUtil.h"

#include "Vector3.h"
#include "Matrix4.h"

Vector4::Vector4()
{
}


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


Vector4& Vector4::operator = (const Vector3& a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = 1.0f;

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
	Vector4 result;
	for (int col=0; col < 4; col++)
	{
		float sum = 0; 

		for (int row=0; row<4; row++)
		{
			sum+=(M[row]*a.M[row][col]);
		} 

		result.M[col] = sum;
	} 

	return result;
}


void Vector4::zero()
{
	x = y = z = 0.0f;
	w = 1.0f;
}


void Vector4::init(float x,float y,float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1.0f;
}


void Vector4::init(float x,float y,float z,float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}


void Vector4::normalize()
{
	// 计算向量模
	float length = sqrtf(x*x + y*y + z*z);

	// 检查除零
	if (length > epsilon_e4) 
	{
		float lengthInv = 1.0f/length;

		// compute normalized version of vector
		x *= lengthInv;
		y *= lengthInv;
		z *= lengthInv;
		w  = 1.0f;
	}
}


void Vector4::Homogenous()
{
	this->x/=w;
	this->y/=w;
	this->z/=w;
	this->w/=w;
}