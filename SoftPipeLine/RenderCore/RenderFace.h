/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   渲染面片
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _RenderFace_H_
#define _RenderFace_H_

#include "../Math/MathUtil.h"

class RenderFace
{
public:
	/// \brief 构造函数
	RenderFace();

	/// \brief 析构函数
	~RenderFace();

public:
	/// \brief 面片的三个顶点
	Vector4 v0;
	Vector4 v1;
	Vector4 v2;
};

#endif