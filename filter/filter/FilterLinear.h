#ifndef FilterL_
#define FilterL_

#include "Filter.h"
#include "Array.h"
#include "Image.h"
#include "Vec3.h"

using namespace imaging;
using namespace std;
using namespace math;
class FilterLinear :virtual public Filter 
{
private:
	element a, c;
public:

	FilterLinear(element FirstVec3,element SecVec3)
	{
		a = FirstVec3;
		c = SecVec3;
	}

	Image operator << (const Image & image)
	{
		Image NewImage;
		element NewElement;
		for (unsigned int i=0; i < image.getHeight(); i++)
		{
			for (unsigned int j=0; j < image.getWidth(); j++)
			{
				NewElement =a*(image.getItem(i,j))-c;
				NewElement.clampToLowerBound(0);
				NewElement.clampToUpperBound(1);
				NewImage.setItem(i, j, NewElement);
			}
		}
		return NewImage;
		

	}
};

#endif