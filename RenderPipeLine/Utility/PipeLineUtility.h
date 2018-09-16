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
#include "..\Mathematics\Int2.h"
#include "RenderBuffer.h"

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

struct RenderContext;

class RenderPipeLine
{
public:
	/// brief 绘制直线
	static void DrawLine(int2 position0, int2 position1, DWORD color, DrawLineType type);

	static void DrawCall(const RenderContext* context, const RenderBuffer& renderBuffer);

	/// \brief 光栅化
	static void Rasterize_Standard(tuple<int2, float4> v0, tuple<int2, float4> v1, tuple<int2, float4> v2);
	static vector<tuple<int2, float4>> SplitTriangle_Standard(tuple<int2, float4> v0, tuple<int2, float4> v1, tuple<int2, float4> v2);
	static void RasterizeFace_Standard(tuple<int2, float4> v0, tuple<int2, float4> v1, tuple<int2, float4> v2);
	static void Rasterize_Barycentric(const RenderContext* context, tuple<int2, float4, float3> v0, tuple<int2, float4, float3> v1, tuple<int2, float4, float3> v2);
	static void Rasterize_WireFrame(int2 v0, int2 v1, int2 v2);

	static void SetViewPortData(int width, int height);

private:
	static Matrix m_ViewPortMatrix;
};

#endif