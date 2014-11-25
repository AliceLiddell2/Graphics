
#pragma once

#include "graphics\Common.h"

namespace MyGL
{
	/// Interface for elementary or compound object 
	///    
	class ILighting 
	{
	public:
		virtual Color& BackColor() =0; 
	};

} // namespace MyGL

