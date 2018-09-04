/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   ��Ⱦ���ߴ�����
/// \author  xizaixuan
/// \date    2018-07
/////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "..\Mathematics\Float3.h"
#include "..\Mathematics\Matrix.h"

using namespace std;

#ifndef PipeLineUtility_H_
#define PipeLineUtility_H_

#define SAFE_RELEASE(P) if(P != nullptr){P->Release() ; P = nullptr;}
#define SAFE_DELETE(P) if(P != nullptr){delete P; P = nullptr;}
#define SAFE_DELETE_ARRAY(P) if(P != nullptr){delete[] P; P = nullptr;}

enum DrawLineType
{
	DDA,
	Bresenham,
};

class RenderPipeLine
{
public:
	/// brief ����ֱ��
	static void DrawLine(float startX, float startY, float endX, float endY, DWORD color, DrawLineType type);

	static void DrawCall(Matrix viewMat, Matrix projMat, vector<float3> vertices, vector<int> indices);

	static void SplitTriangle(float4& v0, float4& v1, float4& v2, float4& v3, float4& v4, float4& v5);

	/// \brief ��դ��
	static void Rasterize(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2);

	/// \brief ��դ��, v1��v2��y��� �� v1.x < v2.x
	static void RasterizeFace(float4 v0, float4 v1, float4 v2);

	static void SetViewPortData(int width, int height);

private:
	static Matrix m_ViewPortMatrix;
};

#endif