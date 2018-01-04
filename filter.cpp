#include <iostream>
#include <string>
#include "../ppm/ppm.h"
#include "Array.h"
#include "Image.h"
#include "FilterLinear.h"
#include "FilterGamma.h"
#include "Vec3.h"

using namespace std;
using namespace math;
using namespace imaging;

int main(int argc, char* argv[])
{
	vector <string> filters;
	int i = 1;
	string ppmname;
	while(true)
	{
		if (string(argv[i]) == "-f")
		{
			i++;
			if (string(argv[i]) == "gamma")
			{
				filters.push_back(string(argv[i]));
				i++;
				filters.push_back(string(argv[i]));
				i++;
			}
			else
			{
				for (int j = 0; j < 7; j++)
				{
					filters.push_back(string(argv[i]));
					i++;
				}
			}
		}
		else
		{
			ppmname = string(argv[i]);
			break;
		}
	}

	const string filename = ppmname;
	reverse(ppmname.begin(), ppmname.end());
	string ppm = ppmname.substr(0,3);
	reverse(ppm.begin(), ppm.end());
	const string format = ppm;
	Image MyImage = Image();
	if (MyImage.load(filename, format))
	{
		int i = 0;
		while (i < filters.size())
		{
			if (string(filters[i]) == "gamma")
			{
				i++;
				FilterGamma filterG = FilterGamma(stof(filters[i]));
				MyImage.setData((filterG << MyImage).getRawDataPtr());
				i++;
			}
			else if (filters[i] == "linear")
			{
				i++;
				element a = element(stof(filters[i]), stof(filters[i + 1]), stof(filters[i + 2]));
				i += 3;
				element c = element(stof(filters[i]), stof(filters[i + 1]), stof(filters[i + 2]));
				i += 3;
				FilterLinear filterL = FilterLinear(a, c);
				MyImage.setData((filterL << MyImage).getRawDataPtr());
			}
			else
			{
				cout << "Wrong Filter!Please try again" << endl;
				break;
			}
		}
	}
	reverse(ppmname.begin(), ppmname.end());
	const string NewFilename = ppmname.insert(0, "filtered_");
	if (MyImage.save(NewFilename, format))//Saving new image
	{
		cout << "File created!" << endl;
	}
	else
	{
		cout << "Could not create file." << endl;
	}
}