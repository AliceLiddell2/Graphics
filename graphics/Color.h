
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
		explicit Color(
			double red, 
			double green, 
			double blue, 
			double alpha=NONTRANSPARENT_ALPHA
			) 
			: color(red, green, blue, alpha) 
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
			*this = other; 
		}

		inline static Color White() 
		{
			return Color(1, 1, 1); 
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

