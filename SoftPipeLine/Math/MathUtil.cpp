#include "MathUtil.h"


float AngelToRadian(float ang)
{
	return ((ang)*PI / 180.0f);
}

float RadianToAngel(float rads)
{
	return ((rads)*180.0f / PI);
}

float Length(const Vector2& v)
{
	return sqrtf(v.x*v.x + v.y*v.y);
}

float Length(const Vector3& v)
{
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

float Length(const Vector4& v)
{
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

Vector2 Normalize(Vector2& v)
{
	//计算模的长度
	float length = Length(v);

	//检查除零
	if (length > epsilon_e5)
	{
		float lengthInv = 1.0f / length;

		v.x = v.x*lengthInv;
		v.y = v.y*lengthInv;
	}

	return v;
}

Vector3 Normalize(Vector3& v)
{
	//计算模的长度
	float length = Length(v);

	//检查除零
	if (length > epsilon_e5)
	{
		float lengthInv = 1.0f / length;

		v.x = v.x*lengthInv;
		v.y = v.y*lengthInv;
		v.z = v.z*lengthInv;
	}

	return v;
}

Vector4 Normalize(Vector4& v)
{
	//计算模的长度
	float length = Length(v);

	//检查除零
	if (length > epsilon_e5)
	{
		float lengthInv = 1.0f / length;

		v.x = v.x*lengthInv;
		v.y = v.y*lengthInv;
		v.z = v.z*lengthInv;
	}

	return v;
}

Vector2 Cross(const Vector2& a, const Vector2& b)
{
	return Vector2(
		a.y*b.x - a.x*b.y,
		a.x*b.y - a.y*b.x);
}

Vector3 Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x);
}

Vector4 Cross(const Vector4& a, const Vector4& b)
{
	return Vector4(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x);
}

template<typename T>
T Zero(T& v)
{
	for (auto m : v.M)
	{
		m = 0.0f;
	}
}

bool isEqual(float a, float b)
{
	return (fabs(a - b) < epsilon_e3);
}