#include "RenderUtil.h"
#include <windows.h>
#include <fstream>
#include "Texture.h"

byte getAValue(DWORD color)
{
	return (LOBYTE((color) >> 24));
}

byte getRValue(DWORD color)
{
	return (LOBYTE((color) >> 16));
}

byte getGValue(DWORD color)
{
	return (LOBYTE((color) >> 8));
}

byte getBValue(DWORD color)
{
	return (LOBYTE(color));
}

DWORD setARGB(byte a, byte r, byte g, byte b)
{
	return (a << 24) + (r << 16) + (g << 8) + b;
}

Texture* LoadTextureFromPNG(std::string path)
{
	Texture* texture = nullptr;

	std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
	
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;

	file.read((char *)&fh, sizeof(BITMAPFILEHEADER));

	if (fh.bfType == 'MB')
	{
		file.read((char *)&ih, sizeof(BITMAPINFOHEADER));

		byte* tempBuf = new byte[ih.biSizeImage];
		file.read((char*)tempBuf, ih.biSizeImage);

		size_t rows = ih.biHeight;
		size_t cols = ih.biWidth;
		DWORD* data = new DWORD[rows*cols];

		for (int index_y = 0; index_y < rows; index_y++)
		{
			// build up 32 bit color word
			for (int index_x = 0; index_x < cols; index_x++)
			{
				// extract RGB components (in BGR order), note the scaling
				byte blue = (tempBuf[index_y*cols * 4 + index_x * 4 + 0]);
				byte green= (tempBuf[index_y*cols * 4 + index_x * 4 + 1]);
				byte red  = (tempBuf[index_y*cols * 4 + index_x * 4 + 2]);

				DWORD color = setARGB(0, red, green, blue);

				// write color to buffer
				DWORD index = index_x + (rows - 1 - index_y)*cols;
				data[index] = color;
			}
		}

		delete tempBuf;
		tempBuf = nullptr;

		texture = new Texture(cols, rows, data);
	}
	
	return texture;
}