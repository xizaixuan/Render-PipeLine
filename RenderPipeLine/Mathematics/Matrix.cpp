#include "Matrix.h"
#include <memory.h>

Matrix::Matrix(void)
{
}

Matrix::Matrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	set(m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33);
}

Matrix::~Matrix(void)
{
}

Matrix& Matrix::operator =(const Matrix& a)
{
	memcpy((void *)(this), (void *)(&a), sizeof(Matrix));

	return *this;
}

Matrix Matrix::operator +(const Matrix& a) const
{
	Matrix result;
	for (int row=0; row<4; row++)
	{
		for (int col=0; col<4; col++)
		{
			result.m[row][col] = m[row][col] + a.m[row][col];
		}
	}
	return result;
}

Matrix Matrix::operator *(const Matrix& a) const
{
	Matrix result;
	for (int row=0; row<4; row++)
	{
		for (int col=0; col<4; col++)
		{
			for (int index=0; index<4; index++)
			{
				result.m[row][col] += m[row][index] * a.m[index][col];
			}
		}
	} 
	return result;
}

void Matrix::identity()
{
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
	m[0][1] = m[0][2] = m[0][3] = 0.0f;
	m[1][0] = m[1][2] = m[1][3] = 0.0f;
	m[2][0] = m[2][1] = m[2][3] = 0.0f;
	m[3][0] = m[3][1] = m[3][2] = 0.0f;
}

void Matrix::set(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	m[0][0] = m00;	m[0][1] = m01;	m[0][2] = m02;	m[0][3] = m03;
	m[1][0] = m10;	m[1][1] = m11;	m[1][2] = m12;	m[1][3] = m13;
	m[2][0] = m20;	m[2][1] = m21;	m[2][2] = m22;	m[2][3] = m23;
	m[3][0] = m30;	m[3][1] = m31;	m[3][2] = m32;	m[3][3] = m33;
}