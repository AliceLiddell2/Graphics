
#pragma once

#include "graphics\Common.h"

#define NONTRANSPARENT_ALPHA (1)

namespace MyGL
{
	class Color
	{
	protected:
		Vector4d* color;

	public:
		explicit Color(
			double red, 
			double green, 
			double blue, 
			double alpha=NONTRANSPARENT_ALPHA
			) 
			// color(red, green, blue, alpha) 
		{
			color = new Vector4d();
			(*color)[0] = red;
			(*color)[1] = green;
			(*color)[2] = blue;
			(*color)[3] = alpha;
		}

		inline double Red()		const 	{ return (*color)[0]; }
		inline double Green()	const 	{ return (*color)[1]; }
		inline double Blue()	const 	{ return (*color)[2]; }
		inline double Alpha()	const 	{ return (*color)[3]; }

		inline double& operator [](int j) { return (*color)[j]; }
		inline const double& operator [](int j) const { return (*color)[j]; }
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

		inline void Output() const 
		{
			char s[1024];
			sprintf(s, "color(%02f, %02f, %02f, %02f)", Red(), Green(), Blue(), Alpha());
			cout << s << endl; 
		}

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Colors 

		inline static Color Chocolate() 
		{
			return Color(210.0/255, 105.0/255, 30.0/255); 
		}

		inline static Color LightGoldenrodYellow() 
		{
			return Color(250.0/255, 250.0/255, 210.0/255); 
		}
		inline static Color SpringGreen() 
		{
			return Color(0.0/255, 255.0/255, 127.0/255); 
		}
		inline static Color PaleGreen() 
		{
			return Color(152.0/255, 251.0/255, 152.0/255); 
		}
		inline static Color MidnightBlue() 
		{
			return Color(25.0/255, 25.0/255, 112.0/255); 
		}
		inline static Color SeaGreen()
		{
			return Color(46.0/255, 139.0/255, 87.0/255); 
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

