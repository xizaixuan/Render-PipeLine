#include "Texture.h"
#include "RenderUtil.h"

Texture::Texture(int width, int height, DWORD* data)
	: mWidth(width)
	, mHeight(height)
	, mData(data)
{
}

Texture::~Texture()
{
	if (mData)
	{
		delete[] mData;
		mData = nullptr;
	}
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}

DWORD Texture::getPixel(float u,float v)
{
	if(u < 0.0f)
		u = 0.0f;

	if(v < 0.0f)
		v = 0.0f;

	if (u > 1.0f)
		u = 1.0f;

	if (v > 1.0f)
		v = 1.0f;

	int x = (mWidth-1)*u;
	int y = (mHeight-1)*v;
	
	DWORD color = mData[x + y*mWidth];

	return color;
}