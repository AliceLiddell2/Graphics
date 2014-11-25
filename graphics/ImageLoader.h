
#pragma once

#include <fstream>

#include "Common.h"

using namespace std;

namespace MyGL
{
	class Image 
	{
	public:
		Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
		{
		}

		~Image()
		{
			if (pixels) delete[] pixels;
		}
		
		/* An array of the form (R1, G1, B1, R2, G2, B2, ...) indicating the
		 * color of each pixel in image.  Color components range from 0 to 255.
		 * The array starts the bottom-left pixel, then moves right to the end
		 * of the row, then moves up to the next column, and so on.  This is the
		 * format in which OpenGL likes images.
		 */
		char* pixels;
		int width;
		int height;


		// Reads a bitmap image from file

		inline static Image* loadBMP(const char* filename)
		{
			ifstream input;
			input.open(filename, ifstream::binary);
			if (input.fail())
			{
				ThrowException(string("Could not find file: ") + filename);
			}
			//
			char buffer[2];
			input.read(buffer, 2);
			if (!(buffer[0] == 'B' && buffer[1] == 'M'))
			{
				ThrowException(string("Not a bitmap file: ") + filename);
			}
			input.ignore(8);
			int dataOffset = readInt(input);
			//
			// Reading the header
			//
			int headerSize = readInt(input);
			int width;
			int height;
			switch(headerSize) 
			{
			case 40:
				{
					// V3
					width = readInt(input);
					height = readInt(input);
					input.ignore(2);
					if (readShort(input) != 24)
					{
						ThrowException(string("Image is not 24 bits per pixel: ") + filename);
					}
					if (readShort(input) != 0)
					{
						ThrowException(string("Image is compressed: ") + filename);
					}
					break;
				}
			case 12:
				{
					// OS/2 V1
					width = readShort(input);
					height = readShort(input);
					input.ignore(2);
					if (readShort(input) != 24)
					{
						ThrowException(string("Image is not 24 bits per pixel: ") + filename);
					}
					break;
				}
			case 64:
					// OS/2 V2
					ThrowException(string("OS/2 V2 bitmaps are not supported: ") + filename);
					break; // never reached 
			case 108:
					// Windows V4
					ThrowException(string("Windows V4 bitmaps are not supported: ") + filename);
					break;
			case 124:
					//Windows V5
					ThrowException(string("Windows V5 bitmaps are not supported: ") + filename);
					break;
			default:
					ThrowException(string("Unknown bitmap format: ") + filename);
			}
			//
			// Reading the data
			//
			int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
			int size = bytesPerRow * height;
			auto_array<char> pixels(new char[size]);
			input.seekg(dataOffset, ios_base::beg);
			input.read(pixels.get(), size);
			//
			// Get the data into the right format
			//
			auto_array<char> pixels2(new char[width * height * 3]);
			//
			for(int y = 0; y < height; y++) 
			{
				for(int x = 0; x < width; x++) 
				{
					for(int c = 0; c < 3; c++) 
					{
						pixels2[3 * (width * y + x) + c] = pixels[bytesPerRow * y + 3 * x + (2 - c)];
					}
				}
			}
			//
			input.close();
			return new Image(pixels2.release(), width, height);
		}



		// --------------------------------------------------------------------------------------------------
		// Misc 

		/// Converts a four-character array to an integer, using little-endian form
		///
		inline static int toInt(const char* bytes) 
		{
			return (int)(
				((unsigned char)bytes[3] << 24) |
				((unsigned char)bytes[2] << 16) |
				((unsigned char)bytes[1] << 8) |
				((unsigned char)bytes[0])
				);
		}
	
		/// Converts a two-character array to a short, using little-endian form
		///
		inline static short toShort(const char* bytes) 
		{
			return (short)(
				((unsigned char)bytes[1] << 8) |
				((unsigned char)bytes[0])
				);
		}
	
		/// Reads the next four bytes as an integer, using little-endian form
		///
		inline static int readInt(ifstream &input) 
		{
			char buffer[4];
			input.read(buffer, 4);
			return toInt(buffer);
		}
	
		/// Reads the next two bytes as a short, using little-endian form
		///
		inline static short readShort(ifstream &input) 
		{
			char buffer[2];
			input.read(buffer, 2);
			return toShort(buffer);
		}
	
		/// Just like auto_ptr, but for arrays
		///
		template<class T>
		class auto_array 
		{
		private:
			T* array;
			mutable bool isReleased;

		public:
			explicit auto_array(T* array_ = NULL) : array(array_), isReleased(false) 
			{
			}
			
			auto_array(const auto_array<T> &aarray) 
			{
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}

			inline void _clear_array()
			{
				if ((!isReleased) && (array != NULL)) 
				{
					delete[] array;
				}
			}
			
			~auto_array() 
			{
				_clear_array(); 
			}
			
			T* get() const 
			{
				return array;
			}
			
			T& operator *() const 
			{
				return *array;
			}
			
			void operator =(const auto_array<T> &aarray) 
			{
				_clear_array(); 
				// 
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}
			
			T* operator ->() const 
			{
				return array;
			}
			
			T* release() 
			{
				isReleased = true;
				return array;
			}
			
			void reset(T* array_ = NULL) 
			{
				_clear_array(); 
				// 
				array = array_;
			}
			
			T* operator +(int i) 
			{
				return array + i; // like for pointers 
			}
			
			T& operator [](int i) 
			{
				return array[i];
			}
		};
	};

} // namespace MyGL 
