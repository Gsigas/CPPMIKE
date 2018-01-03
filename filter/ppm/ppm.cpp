#include <iostream>
#include <string>
#include <fstream>
#include "ppm.h"




using namespace std;
using namespace imaging;

float * imaging::ReadPPM(const char * filename, int * w, int * h)
{
	ifstream iFile(filename, ios::in | ios::binary);
	if (!iFile.is_open())
	{
		printf("Could not open File\n");
		return nullptr;
	}
	string type,input,Smaxpix,Swidth,Sheight;
	type = "";
	Smaxpix = "";
	Swidth = "";
	Swidth = "";
	int maxpix=0;
	int Spacecounter = 0;
	while (Smaxpix == "")
	{
		getline(iFile, input);
		string Allstrings = "";
		if(input.empty() || Spacecounter>=2)
		{
			if (type == "")
			{
				cout << "The File format is Missing!" << endl;
				return nullptr;
			}
			else if(Swidth=="")
			{
				cout << "The Width is Missing!" << endl;
				return nullptr;
			}
			else if (Sheight == "")
			{
				cout << "The Height is Missing!" << endl;
				return nullptr;
			}
			else
			{
				cout << "The max Value is Missing!" << endl;
				return nullptr;
			}
		}
		
		Spacecounter = 0;
		int i = 0;
		while(i < input.size() && Spacecounter<2)
		{
			if (type == "")
			{
				while (!isspace(input[i]) && i <input.size())
				{
					type+=input[i];
					Allstrings = input[i];
					i++;
					Spacecounter = 0;
				}
				Allstrings += " ";
				Spacecounter++;
				i++;
			}
			if (Swidth=="" && i < input.size() && Spacecounter < 2)
			{
				while (!isspace(input[i]) && i <input.size())
				{
					Swidth += input[i];
					Allstrings = input[i];
					i++;
					Spacecounter = 0;
				}
				Allstrings += " ";
				Spacecounter++;
				i++;
			}
			if (Sheight == "" && i < input.size() && Spacecounter < 2)
			{
				while (!isspace(input[i]) && i <input.size())
				{
					Sheight += input[i];
					Allstrings = input[i];
					i++;
					Spacecounter = 0;
				}
				Allstrings += " ";
				Spacecounter++;
				i++;
			}
			if (Smaxpix == "" && i < input.size() && Spacecounter < 2)
			{
				while (!isspace(input[i]) && i <input.size())
				{
					Smaxpix += input[i];
					Allstrings = input[i];
					i++;
					Spacecounter = 0;
				}
				Allstrings += " ";
				Spacecounter++;
				i++;
				if (type != ""&& Swidth != "" &&Sheight != "" &&Smaxpix != "" && i < input.size())
				{
					long pos = iFile.tellg();
					iFile.seekg(pos - (pos - sizeof(Allstrings)));
					break;
				}
			}
		}

	}
	if (type.compare("P6") != 0)
	{
		printf("Wrong File type!\n");
		return nullptr;
	}
	*w = atoi(Swidth.c_str());
	*h = atoi(Sheight.c_str());
	maxpix = atoi(Smaxpix.c_str());
	if (maxpix > 255)
	{
		printf("Max pixel value>255\n");
		return nullptr;
	}
	
	int size = (*w)*(*h) * 3;
	unsigned char *temp = new unsigned char[(*h)* (*w) * 3];
	iFile.read((char*)temp, size);
	float * MyArray = new float[size];
	for (int i = 0; i < size; i++)
	{
		int x = int(temp[i]);
		MyArray[i] = x / 255.0F;
	}
	iFile.close();
	delete temp;
	return MyArray;
}



bool imaging::WritePPM(const float * data, int w, int h, const char * filename)
{
	ofstream oFile(filename, ios::out | ios::binary);
	string text = "P6\n" + to_string(w) + "\n" + to_string(h) + "\n255\n";
	oFile.write(text.c_str(), text.size());
	int size = w*h * 3;
	unsigned char *Array = new unsigned char[w*h * 3];
	for (int i = 0; i < size; i++)
	{
		Array[i] = data[i] * (float)255.0;
	}
	oFile.write((char*)Array, size);
	oFile.flush();
	oFile.clear();
	oFile.close();
	delete Array;
	return true;
}

