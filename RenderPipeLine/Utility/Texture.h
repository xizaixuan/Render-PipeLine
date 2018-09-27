#ifndef _Texture_H_
#define _Texture_H_

#include <windows.h>

class Texture
{
public:
	/// brief 参数构造函数
	Texture(int width, int height, DWORD* data);

	/// brief 析构函数
	~Texture();

public:
	/// brief 获取width
	int getWidth();

	/// brief 获取height
	int getHeight();

	/// brief 获取像素
	DWORD getPixel(float u, float v);

private:
	/// 纹理宽度
	int m_Width;

	/// 纹理高度
	int m_Height;

	/// 纹理数据
	DWORD* m_Data;
};


#endif
