/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   Джх╬иообнд
/// \author  xizaixuan
/// \date    2018-09
/////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "../Mathematics/Float3.h"
#include "../Mathematics/Matrix.h"
using namespace std;

#ifndef RenderContext_H_
#define RenderContext_H_


struct RenderContext
{
	RenderContext();

	float3 CameraPosition;
	Matrix ViewMatrix;
	Matrix ProjMatrix;
};

#endif