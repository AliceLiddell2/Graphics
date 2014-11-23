
#pragma once

#include "graphics\Common.h"
#include "graphics\Color.h"

namespace MyGL
{
	/// Interface for elementary or compound object 
	///    
	class IElement
	{
	public:
		// Drawing

		virtual void Draw() const =0; 

		// Surface properties

		virtual Color& SurfaceColor() =0;

		virtual bool& IsAMirror() =0; 

		virtual Plane ReflectionPlane() =0;
	};

} // namespace MyGL

