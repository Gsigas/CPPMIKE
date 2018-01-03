#ifndef Filter_
#define Filter_

#include "Image.h"

using namespace std;
using namespace imaging;
class Filter
{
public:
	Filter(){}

	Filter(const Filter & src) {}

	virtual Image operator << (const Image & image) = 0;
};

#endif

