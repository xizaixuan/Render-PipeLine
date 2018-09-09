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

struct RenderContext;

class RenderPipeLine
{
public:
	/// brief ����ֱ��
	static void DrawLine(float startX, float startY, float endX, float endY, DWORD color, DrawLineType type);

	static void DrawCall(RenderContext* context, vector<float3> vertices, vector<int> indices, vector<float3> normals);

	/// \brief ��դ��
	static void Rasterize_Standard(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2);
	static vector<tuple<float4>> SplitTriangle_Standard(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2);
	static void RasterizeFace_Standard(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2);
	static void Rasterize_Barycentric(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2);
	static void Rasterize_WireFrame(tuple<float4> v0, tuple<float4> v1, tuple<float4> v2);

	static void SetViewPortData(int width, int height);

private:
	static Matrix m_ViewPortMatrix;
};

#endif