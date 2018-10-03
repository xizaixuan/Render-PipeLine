#ifndef _Texture_H_
#define _Texture_H_

#include <windows.h>

class Texture
{
public:
	/// brief �������캯��
	Texture(int width, int height, DWORD* data);

	/// brief ��������
	~Texture();

public:
	/// brief ��ȡwidth
	int getWidth();

	/// brief ��ȡheight
	int getHeight();

	/// brief ��ȡ����
	DWORD getPixel(float u, float v);

private:
	/// ��������
	int m_Width;

	/// �����߶�
	int m_Height;

	/// ��������
	DWORD* m_Data;
};


#endif