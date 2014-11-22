
#pragma once

#include "graphics/Common.h"

#define NONTRANSPARENT_ALPHA (1)

namespace MyGL
{
	class Color
	{
	protected:
		Vector4d color;

	public:
		Color(double red, double green, double blue) : color(red, green, blue, NONTRANSPARENT_ALPHA) 
		{
		}

		inline double Red() 	{ return color[0]; }
		inline double Green() 	{ return color[1]; }
		inline double Blue() 	{ return color[2]; }

		inline const Color& operator =(const Color& other)
		{
			color = other.color;
			return other;
		}

		Color(const Color& other)
		{
			*this = color; 
		}

		// ----
		// Shading tecniques

		Color Compose(const Color& infront, const Color& behind)
		{
			// TODO: compose alpha in a right way 
			return infront;
		}
	};

} // namespace MyGL

