#include "MathUtil.h"

float MathUtil::AngelToRadian(float ang)
{
	return ((ang)*PI / 180.0f);
}

float MathUtil::RadianToAngel(float rads)
{
	return ((rads)*180.0f / PI);
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
	if (length > EPSILON)
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
	if (length > EPSILON)
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
	if (length > EPSILON)
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

bool MathUtil::IsEqual(float a, float b)
{
	return (fabs(a - b) <= EPSILON);
}

Matrix MathUtil::inverse(Matrix mat)
{
	Matrix imat;

	float det = (
		mat.m[0][0] * (mat.m[1][1] * mat.m[2][2] - mat.m[1][2] * mat.m[2][1]) -
		mat.m[0][1] * (mat.m[1][0] * mat.m[2][2] - mat.m[1][2] * mat.m[2][0]) +
		mat.m[0][2] * (mat.m[1][0] * mat.m[2][1] - mat.m[1][1] * mat.m[2][0]));

	// 检查除零
	if (fabs(det) > MathUtil::EPSILON)
	{
		float det_inv = 1.0f / det;

		imat.m[0][0] = det_inv * (mat.m[1][1] * mat.m[2][2] - mat.m[1][2] * mat.m[2][1]);
		imat.m[0][1] =-det_inv * (mat.m[0][1] * mat.m[2][2] - mat.m[0][2] * mat.m[2][1]);
		imat.m[0][2] = det_inv * (mat.m[0][1] * mat.m[1][2] - mat.m[0][2] * mat.m[1][1]);
		imat.m[0][3] = 0.0f;

		imat.m[1][0] =-det_inv * (mat.m[1][0] * mat.m[2][2] - mat.m[1][2] * mat.m[2][0]);
		imat.m[1][1] = det_inv * (mat.m[0][0] * mat.m[2][2] - mat.m[0][2] * mat.m[2][0]);
		imat.m[1][2] =-det_inv * (mat.m[0][0] * mat.m[1][2] - mat.m[0][2] * mat.m[1][0]);
		imat.m[1][3] = 0.0f;

		imat.m[2][0] = det_inv * (mat.m[1][0] * mat.m[2][1] - mat.m[1][1] * mat.m[2][0]);
		imat.m[2][1] =-det_inv * (mat.m[0][0] * mat.m[2][1] - mat.m[0][1] * mat.m[2][0]);
		imat.m[2][2] = det_inv * (mat.m[0][0] * mat.m[1][1] - mat.m[0][1] * mat.m[1][0]);
		imat.m[2][3] = 0.0f;

		imat.m[3][0] = -(mat.m[3][0] * mat.m[0][0] + mat.m[3][1] * mat.m[1][0] + mat.m[3][2] * mat.m[2][0]);
		imat.m[3][1] = -(mat.m[3][0] * mat.m[0][1] + mat.m[3][1] * mat.m[1][1] + mat.m[3][2] * mat.m[2][1]);
		imat.m[3][2] = -(mat.m[3][0] * mat.m[0][2] + mat.m[3][1] * mat.m[1][2] + mat.m[3][2] * mat.m[2][2]);
		imat.m[3][3] = 1.0f;
	}

	return mat;
}
