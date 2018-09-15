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
#include "..\Mathematics\Int2.h"

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
	static void DrawLine(int2 position0, int2 position1, DWORD color, DrawLineType type);

	static void DrawCall(RenderContext* context, vector<float3> vertices, vector<int> indices, vector<float3> normals, vector<float4> colors);

	/// \brief ��դ��
	static void Rasterize_Standard(tuple<int2> v0, tuple<int2> v1, tuple<int2> v2);
	static vector<tuple<int2>> SplitTriangle_Standard(tuple<int2> v0, tuple<int2> v1, tuple<int2> v2);
	static void RasterizeFace_Standard(tuple<int2> v0, tuple<int2> v1, tuple<int2> v2);
	static void Rasterize_Barycentric(tuple<int2, float4> v0, tuple<int2, float4> v1, tuple<int2, float4> v2);
	static void Rasterize_WireFrame(int2 v0, int2 v1, int2 v2);

	static void SetViewPortData(int width, int height);

private:
	static Matrix m_ViewPortMatrix;
};

#endif