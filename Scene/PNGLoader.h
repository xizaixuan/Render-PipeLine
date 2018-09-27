/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   PngÕº∆¨‘ÿ»Î
/// \author  xizaixuan
/// \date    2017-09
/////////////////////////////////////////////////////////////////////////////////
#ifndef PNGLoader_H_
#define PNGLoader_H_

#include <string>
#include "../RenderPipeLine/Utility/Singleton.h"
#include "../RenderPipeLine/Utility/Texture.h"

using namespace std;
class PNGLoader : public Singleton<PNGLoader>
{
	SINGLETON_DEFINE(PNGLoader)

private:
	PNGLoader();
	~PNGLoader();

public:
	Texture* LoadTexture(string path);
};

#endif