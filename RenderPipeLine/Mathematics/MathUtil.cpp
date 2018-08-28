#include "MathUtil.h"

float MathUtil::AngelToRadian(float ang)
{
	return ((ang)*pi / 180.0f);
}

float MathUtil::RadianToAngel(float rads)
{
	return ((rads)*180.0f / pi);
}

float MathUtil::Length(const float2& v)
{
	return sqrtf(v.x*v.x + v.y*v.y);
}

float MathUtil::Length(const float3& v)
{
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

float MathUtil::Length(const float4& v)
{
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

float2 MathUtil::Normalize(float2& v)
{
	//计算模的长度
	float length = Length(v);

	//检查除零
	if (length > epsilon)
	{
		float lengthInv = 1.0f / length;

		v.x = v.x*lengthInv;
		v.y = v.y*lengthInv;
	}

	return v;
}

float3 MathUtil::Normalize(float3& v)
{
	//计算模的长度
	float length = Length(v);

	//检查除零
	if (length > epsilon)
	{
		float lengthInv = 1.0f / length;

		v.x = v.x*lengthInv;
		v.y = v.y*lengthInv;
		v.z = v.z*lengthInv;
	}

	return v;
}

float4 MathUtil::Normalize(float4& v)
{
	//计算模的长度
	float length = Length(v);

	//检查除零
	if (length > epsilon)
	{
		float lengthInv = 1.0f / length;

		v.x = v.x*lengthInv;
		v.y = v.y*lengthInv;
		v.z = v.z*lengthInv;
	}

	return v;
}

float2 MathUtil::Cross(const float2& a, const float2& b)
{
	return float2(
		a.y*b.x - a.x*b.y,
		a.x*b.y - a.y*b.x);
}

float3 MathUtil::Cross(const float3& a, const float3& b)
{
	return float3(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x);
}

float4 MathUtil::Homogenous(float4 & value)
{
	value.x /= value.w;
	value.y /= value.w;
	value.z /= value.w;
	value.w = 1.0f;
	return value;
}

bool MathUtil::IsEqual(float a, float b)
{
	return (fabs(a - b) <= epsilon);
}

Matrix MathUtil::Inverse(Matrix mat)
{
	Matrix imat;

	float det = (
		mat.r0.x * (mat.r1.y * mat.r2.z - mat.r1.z * mat.r2.y) -
		mat.r0.y * (mat.r1.x * mat.r2.z - mat.r1.z * mat.r2.x) +
		mat.r0.z * (mat.r1.x * mat.r2.y - mat.r1.y * mat.r2.x));

	// 检查除零
	if (fabs(det) > MathUtil::epsilon)
	{
		float det_inv = 1.0f / det;

		imat.r0.x = det_inv * (mat.r1.y * mat.r2.z - mat.r1.z * mat.r2.y);
		imat.r0.y =-det_inv * (mat.r0.y * mat.r2.z - mat.r0.z * mat.r2.y);
		imat.r0.z = det_inv * (mat.r0.y * mat.r1.z - mat.r0.z * mat.r1.y);
		imat.r0.w = 0.0f;

		imat.r1.x =-det_inv * (mat.r1.x * mat.r2.z - mat.r1.z * mat.r2.x);
		imat.r1.y = det_inv * (mat.r0.x * mat.r2.z - mat.r0.z * mat.r2.x);
		imat.r1.z =-det_inv * (mat.r0.x * mat.r1.z - mat.r0.z * mat.r1.x);
		imat.r1.w = 0.0f;

		imat.r2.x = det_inv * (mat.r1.x * mat.r2.y - mat.r1.y * mat.r2.x);
		imat.r2.y =-det_inv * (mat.r0.x * mat.r2.y - mat.r0.y * mat.r2.x);
		imat.r2.z = det_inv * (mat.r0.x * mat.r1.y - mat.r0.y * mat.r1.x);
		imat.r2.w = 0.0f;

		imat.r3.x = -(mat.r3.x * imat.r0.x + mat.r3.y * imat.r1.x + mat.r3.z * imat.r2.x);
		imat.r3.y = -(mat.r3.x * imat.r0.y + mat.r3.y * imat.r1.y + mat.r3.z * imat.r2.y);
		imat.r3.z = -(mat.r3.x * imat.r0.z + mat.r3.y * imat.r1.z + mat.r3.z * imat.r2.z);
		imat.r3.w = 1.0f;
	}

	return imat;
}