#ifndef FilterG_
#define FilterG_

#include "Filter.h"

using namespace imaging;
using namespace std;

class FilterGamma :virtual public Filter
{
private:
	float g;
public:

	FilterGamma(){}

	FilterGamma(float gamma)
	{
		if (gamma < 0.5)
		{
			g = 0.5;
		}
		else if (gamma > 2.0)
		{
			g = 2.0;
		}
		else
		{
			g = gamma;
		}
	}

	FilterGamma(const FilterGamma &src)
	{
		g = src.g;
	}
	~FilterGamma(){}

	Image operator << (const Image & image)
	{
		Image NewImage=Image(image.getWidth(), image.getHeight());
		for (int i=0; i < image.getHeight(); i++)
		{
			for (int j=0; j < image.getWidth(); j++)
			{
				element NewElement = image.getItem(i,j);
				NewElement.x=pow(NewElement.x, g);
				NewElement.y=pow(NewElement.y, g);
				NewElement.z=pow(NewElement.z, g);
				NewImage.setItem(i, j, NewElement);
			}
		}
		return NewImage;

	}
};
#endif
