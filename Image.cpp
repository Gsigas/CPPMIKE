#include <iostream>
#include "Array.h"
#include "Image.h"
#include "../ppm/ppm.h"
#include <string>

using namespace std;
using namespace imaging;
	//Constructors
	//Default Constructor
	
Image::Image() :math::Array<element>() {}

Image::Image(unsigned int width, unsigned int height) : math::Array<element>(width, height) {}

Image::Image(unsigned int width, unsigned int height, const vector<element> data_ptr) : math::Array<element>(width, height, data_ptr) {}

	//Copy Constructor
Image::Image(const Image &src):math::Array<element>(src) {}

	//Destructor
Image::~Image() {}


bool imaging::Image::load(const std::string & filename, const std::string & format)
{
	if ((format.compare("ppm") == 0) || (format.compare("PPM") == 0)) //case-insensitive
	{
		int w1;
		int h1;
		const char* file_ptr = &filename[0];// points at filename
		float* F_Data = ReadPPM(file_ptr, &w1, &h1); //w,h are unsigned int on Image, but int on ReadPPM
		width = (unsigned int)w1;
		height = (unsigned int)h1;
		int j = 0;
		for (int i = 0; i < width*height * 3; i += 3)
		{
			buffer.push_back(element(F_Data[i], F_Data[i + 1], F_Data[i + 2]));
		}
		return true;
	}
	cout << "The input File is not a PPM" << endl;
	return false;
}

bool imaging::Image::save(const std::string & filename, const std::string & format)
{
	if ((format.compare("ppm") == 0) || (format.compare("PPM") == 0)) //case-insensitive
	{
		const char* file_ptr = &filename[0];
		float* Data = new float[height*width * 3];
		int j = 0;
		for (int i = 0; i <(height)*(width); i++)
		{
			Data[j] = (buffer[i]).x;
			Data[j + 1] = (buffer[i]).y;
			Data[j + 2] = (buffer[i]).z;
			j += 3;
		}
		return WritePPM(Data, width, height, file_ptr);
	}
	return false;
}