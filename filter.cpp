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
	vector <Filter*> filters;
	int i = 1;
	string ppmname;
	while(true)
	{
		if (string(argv[i]) == "-f")
		{
			i++;
			if (string(argv[i]) == "gamma")
			{
				FilterGamma *filterG =new  FilterGamma(stof(argv[i+1]));
				filters.push_back(filterG);
				i+=2;
			}
			else if (string(argv[i]) == "linear")
			{
				element a = element(stof(argv[i+1]), stof(argv[i + 2]), stof(argv[i + 3]));
				element c = element(stof(argv[i + 4]), stof(argv[i + 5]), stof(argv[i + 6]));
				FilterLinear *filterL =new  FilterLinear(a, c);
				filters.push_back(filterL);
				i += 7;
			}
			else
			{
				cout << "Wrong input!" << endl;
				break;
			}
		}
		else
		{
			ppmname = string(argv[i]);
			break;
		}
	}

	const string filename = ppmname;
	const string format = ppmname.substr(ppmname.find_last_of(".") + 1);
	Image MyImage = Image();
	if (MyImage.load(filename, format))
	{
		for (int i = 0; i < filters.size(); i++)
		{
			MyImage.setData((*filters[i] << MyImage).getRawDataPtr());
		}
	}
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