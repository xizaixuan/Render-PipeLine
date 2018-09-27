#include "Texture.h"
#include "../Mathematics/MathUtil.h"

Texture::Texture(int width, int height, DWORD* data)
	: m_Width(width)
	, m_Height(height)
	, m_Data(data)
{
}

Texture::~Texture()
{
	if (m_Data)
	{
		delete[] m_Data;
		m_Data = nullptr;
	}
}

int Texture::getWidth()
{
	return m_Width;
}

int Texture::getHeight()
{
	return m_Height;
}

DWORD Texture::getPixel(float u, float v)
{
	u = MathUtil::Clamp(u, 0.0f, 1.0f);
	v = MathUtil::Clamp(v, 0.0f, 1.0f);

	int x = (m_Width-1)*u;
	int y = (m_Height-1)*v;
	
	DWORD color = m_Data[x + y*m_Width];

	return color;
}