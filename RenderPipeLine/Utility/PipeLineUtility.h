/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   渲染管线处理函数
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
	/// brief 绘制直线
	static void DrawLine(float startX, float startY, float endX, float endY, DWORD color, DrawLineType type);

	static void DrawCall(Matrix viewMat, Matrix projMat, vector<float3> vertices, vector<int> indices);

	static void SplitTriangle(float4& v0, float4& v1, float4& v2, float4& v3, float4& v4, float4& v5);

	/// \brief 光栅化
	static void Rasterize(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2);

	/// \brief 光栅化, v1和v2的y相等 且 v1.x < v2.x
	static void RasterizeFace(float4 v0, float4 v1, float4 v2);

	static void SetViewPortData(int width, int height);

private:
	static Matrix m_ViewPortMatrix;
};

#endif