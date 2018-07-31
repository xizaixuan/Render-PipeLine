/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   渲染管线处理函数
/// \author  xizaixuan
/// \date    2018-07
/////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <cstdlib>
#include<algorithm>

#ifndef PipeLineUtility_H_
#define PipeLineUtility_H_

#define SAFE_RELEASE(P) if(P != nullptr){P->Release() ; P = nullptr;}
#define SAFE_DELETE(P) if(P != nullptr){delete P; P = nullptr;}
#define SAFE_DELETE_ARRAY(P) if(P != nullptr){delete[] P; P = nullptr;}

/// brief 绘制直线
void drawLineWithDDA(float startX, float startY, float endX, float endY);

/// brief 绘制直线
void drawLineWithBresenham(float startX, float startY, float endX, float endY);

#endif