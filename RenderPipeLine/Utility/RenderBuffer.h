/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   äÖÈ¾Êý¾Ý¼¯
/// \author  xizaixuan
/// \date    2018-09
/////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "../Mathematics/Float3.h"
using namespace std;

#ifndef RenderBuffer_H_
#define RenderBuffer_H_


struct RenderBuffer
{
	vector<float3>	vertices;
	vector<int>		indices;
};

#endif