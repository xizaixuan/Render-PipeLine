/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   渲染常用函数或常量
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////

#ifndef _RenderUtil_H_
#define _RenderUtil_H_

#include <windows.h>
#include "../Math/MathUtil.h"
#include <string>

byte getAValue(DWORD color);
byte getRValue(DWORD color);
byte getGValue(DWORD color);
byte getBValue(DWORD color);

DWORD setARGB(byte a, byte r, byte g, byte b);

class Texture;

Texture* LoadTextureFromPNG(std::string path);

#endif
