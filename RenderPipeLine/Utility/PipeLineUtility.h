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

class Camera;

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

	static void PipeLine(Camera* camera, vector<float3> vertices, vector<int> indices);

	static void SetViewPortData(int width, int height);

	static Matrix m_ViewPortMatrix;
};

#endif