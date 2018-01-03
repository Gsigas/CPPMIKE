#ifndef _Array
#define _Array
#include <string>
#include <vector>
using namespace std;

namespace math
{
	template <typename T> class Array
	{
	protected:
		vector<T> buffer;
		unsigned int width, height;

	public:

		const unsigned int getWidth() const { return width; }

		const unsigned int getHeight() const { return height; }

		//Obtains a pointer to the internal data.
		vector<T> getRawDataPtr()
		{
			return buffer;
		}

		//Returns Item at (x,y) position
		T getItem(unsigned int x, unsigned int y) const
		{
			int Item = x*width + y;
			if (Item<width*height)
			{
				return buffer[Item];
			}
			return T(0, 0, 0);
		}


		// data mutator
		void setItem(unsigned int x, unsigned int y, T & value)
		{
			int Item = x*width + y; //pixel number

			if (Item<width*height)
			{
				buffer[Item] = value;
			}
		}
		
		
		void setData(const vector <T> & data_ptr)
		{
			if ((buffer == nullptr) || (width == 0) || (height == 0))
			{
				return;
			}
			buffer = data_ptr;
		}


		// Constructors
	
		// Default constructor
		Array()
		{
			width = 0;
			height = 0;
		}

		Array(unsigned int w, unsigned int h)
		{
			width = w;
			height = h;
		}

		Array(unsigned int w, unsigned int h, const vector <T> data_ptr)
		{
			width = w;
			height = h;
			buffer = data_ptr;
		}

		// Copy constructor
		Array(const Array<T> &src)
		{
			width = src.width;
			height = src.height;
			buffer = src.buffer;
		}

		// Dectructor
		~Array()
		{
				buffer.clear();
		}


		//Operators

		Array<T> & operator = (const Array<T> & right)
		{
			return Array(right);
		}
		
		T& operator ()(int i, int j)
		{
			return buffer[i*width + j];
		}
	};
} //namespace imaging
#endif