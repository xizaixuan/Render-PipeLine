#include "Matrix4.h"

#include <memory.h>
#include "MathUtil.h"


Matrix4::Matrix4(void)
{
}

Matrix4::Matrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
	:	M00(m00),M01(m01),M02(m02),M03(m03),
		M10(m10),M11(m11),M12(m12),M13(m13),
		M20(m20),M21(m21),M22(m22),M23(m23),
		M30(m30),M31(m31),M32(m32),M33(m33)
{}

Matrix4::~Matrix4(void)
{
}

Matrix4& Matrix4::operator =(const Matrix4& a)
{
	memcpy((void *)(this), (void *)(&a), sizeof(Matrix4));

	return *this;
}

Matrix4 Matrix4::operator +(const Matrix4& a) const
{
	Matrix4 result;
	for (int row=0; row<4; row++)
	{
		for (int col=0; col<4; col++)
		{
			result.M[row][col] = M[row][col] + a.M[row][col];
		}
	}
	return result;
}

Matrix4 Matrix4::operator *(const Matrix4& a) const
{
	Matrix4 result;
	for (int row=0; row<4; row++)
	{
		for (int col=0; col<4; col++)
		{
			float sum = 0; 

			for (int index=0; index<4; index++)
			{
				sum+=(M[row][index]*a.M[index][col]);
			}

			result.M[row][col] = sum;
		}
	} 
	return result;
}

void Matrix4::identity()
{
	M[0][0] = M[1][1] = M[2][2] = M[3][3] = 1.0f;
	M[0][1] = M[0][2] = M[0][3] = 0.0f;
	M[1][0] = M[1][2] = M[1][3] = 0.0f;
	M[2][0] = M[2][1] = M[2][3] = 0.0f;
	M[3][0] = M[3][1] = M[3][2] = 0.0f;
}

void Matrix4::init(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	M00=m00;	M01=m01;	M02=m02;	M03=m03;
	M10=m10;	M11=m11;	M12=m12;	M13=m13;
	M20=m20;	M21=m21;	M22=m22;	M23=m23;
	M30=m30;	M31=m31;	M32=m32;	M33=m33;
	
}

Matrix4 Matrix4::inverse()
{
	// 计算该矩阵的逆矩阵
	// 最后一列为 [0 0 0 1]t
	Matrix4 mi;

	float det =  ( M00 * ( M11 * M22 - M12 * M21 ) -
		M01 * ( M10 * M22 - M12 * M20 ) +
		M02 * ( M10 * M21 - M11 * M20 ) );

	// 检查除零
	if (fabs(det) > epsilon_e5)
	{
		float det_inv  = 1.0f / det;

		mi.M00 =  det_inv * ( M11 * M22 - M12 * M21 );
		mi.M01 = -det_inv * ( M01 * M22 - M02 * M21 );
		mi.M02 =  det_inv * ( M01 * M12 - M02 * M11 );
		mi.M03 = 0.0f;

		mi.M10 = -det_inv * ( M10 * M22 - M12 * M20 );
		mi.M11 =  det_inv * ( M00 * M22 - M02 * M20 );
		mi.M12 = -det_inv * ( M00 * M12 - M02 * M10 );
		mi.M13 = 0.0f;

		mi.M20 =  det_inv * ( M10 * M21 - M11 * M20 );
		mi.M21 = -det_inv * ( M00 * M21 - M01 * M20 );
		mi.M22 =  det_inv * ( M00 * M11 - M01 * M10 );
		mi.M23 = 0.0f;

		mi.M30 = -( M30 * mi.M00 + M31 * mi.M10 + M32 * mi.M20 );
		mi.M31 = -( M30 * mi.M01 + M31 * mi.M11 + M32 * mi.M21 );
		mi.M32 = -( M30 * mi.M02 + M31 * mi.M12 + M32 * mi.M22 );
		mi.M33 = 1.0f; 
	}

	return mi;
}

void Matrix4::setTranslate(float x, float y, float z)
{
	M30 = x;
	M31 = y;
	M32 = z;
}

void Matrix4::setTranslate(Vector3 pos)
{
	M30 = pos.x;
	M31 = pos.y;
	M32 = pos.z;
}