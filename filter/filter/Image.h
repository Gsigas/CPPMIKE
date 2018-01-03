//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2017 - 2018
//
//

#ifndef _IMAGE
#define _IMAGE

#include <vector>
#include "Vec3.h"
#include "Array.h"
#include <string>

/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation. 
 */ 
namespace imaging
{

//------------------------------------ class Image ------------------------------------------------

	/*! It is the class that represents a generic data container for an image.
	 * 
	 * It holds the actual buffer of the pixel values and provides methods for accessing them, 
	 * either as individual pixels or as a memory block. The Image class alone does not provide 
	 * any functionality for loading and storing an image, as it is the result or input to such a procedure. 
	 *
	 * The internal buffer of an image object stores the actual bytes (data) of the color image as
	 * a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is 
	 * width X height X sizeof(Color) bytes.
	 *
	 * All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
	 * intensity ranges, each color component is within the range [0.0, 1.0].
	 */ 
	typedef math::Vec3<float> element;

	class Image :public math::Array<element>
	{
	public:

		Image();
		
		Image(unsigned int width, unsigned int height);

		
		Image(unsigned int width, unsigned int height, const vector <element> data_ptr);
		
		Image(const Image &src);
		
		~Image();

		bool load(const std::string & filename, const std::string & format);

		
		bool save(const std::string & filename, const std::string & format);

	};

} //namespace imaging

#endif