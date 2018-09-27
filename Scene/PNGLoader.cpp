#include "PNGLoader.h"
#include <windows.h>
#include <fstream>
#include <vector>
#include "..\Lodepng\lodepng.h"

Texture* PNGLoader::LoadTexture(string filename)
{
	std::vector<unsigned char> png;
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	lodepng::State state; //optionally customize this one

	unsigned error = lodepng::load_file(png, filename); //load the image file with given filename
	if (!error)
		error = lodepng::decode(image, width, height, state, png);

	DWORD* data = new DWORD[width*height];

	for (int row = 0; row < height; row++)
	{
		// build up 32 bit color word
		for (int col = 0; col < width; col++)
		{
			// extract RGB components (in BGR order), note the scaling
			byte blue	= (image[row*width * 4 + col * 4 + 0]);
			byte green	= (image[row*width * 4 + col * 4 + 1]);
			byte red	= (image[row*width * 4 + col * 4 + 2]);

			// write color to buffer
			DWORD index = col + (height - 1 - row)*width;
			DWORD color = (red << 16) + (green << 8) + blue;
			data[index] = color;
		}
	}

	return new Texture(width, height, data);
}
