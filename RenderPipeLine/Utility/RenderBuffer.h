/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   äÖÈ¾Êý¾Ý¼¯
/// \author  xizaixuan
/// \date    2018-09
/////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "../Mathematics/Float3.h"
#include "../Mathematics/Float4.h"
using namespace std;

#ifndef RenderBuffer_H_
#define RenderBuffer_H_


struct RenderBuffer
{
	vector<float3>	vertices;
	vector<float3>	normals;
	vector<int>		indices;
	vector<float4>	colors;
};

#endif