#include "Matrix.h"
#include <memory.h>

Matrix::Matrix(void)
	: r0(0.0f, 0.0f, 0.0f, 0.0f)
	, r1(0.0f, 0.0f, 0.0f, 0.0f)
	, r2(0.0f, 0.0f, 0.0f, 0.0f)
	, r3(0.0f, 0.0f, 0.0f, 0.0f)
{
}

Matrix::Matrix(float4 row0, float4 row1, float4 row2, float4 row3)
	: r0(row0)
	, r1(row1)
	, r2(row2)
	, r3(row3)
{
}

Matrix::~Matrix(void)
{
}

Matrix& Matrix::operator =(const Matrix& a)
{
	memcpy((void *)(this), (void *)(&a), sizeof(Matrix));

	return *this;
}

Matrix Matrix::operator*(const float4 & a) const
{
	return Matrix();
}

Matrix Matrix::operator *(const Matrix& a) const
{
	Matrix mat = (*this);
	return Matrix(mat.r0*a, mat.r1*a, mat.r2*a, mat.r3*a);
}

void Matrix::Identity()
{
	r0 = r1 = r2 = r3 = Float4(0.0f, 0.0f, 0.0f, 0.0f);
	r0.x = r1.y = r2.z = r3.w = 1.0f;
}

void Matrix::Position(float3 position)
{
	r3.x = position.x;
	r3.y = position.y;
	r3.z = position.z;
}