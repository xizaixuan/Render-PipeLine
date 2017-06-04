/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   数学常量及算法
/// \author  zhangxuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _MathUtil_H_
#define _MathUtil_H_

#include <math.h>

const float epsilon_e4 = (float)(1E-4);
const float epsilon_e5 = (float)(1E-5);
const float epsilon_e6 = (float)(1E-6);

// 求向量长度
template<typename T>
float Length(const T& a);

#endif
