
#pragma once

#include "graphics\Common.h"

namespace MyGL
{
	/// Model lighting partial component 
	///    
	class ModelLighting : public ILighting
	{
	protected:
		Color backColor; 

	protected:
		ModelLighting() : backColor(1, 1, 1) 
		{
		} 

	public:
		Color& BackColor() // final 
		{
			return backColor; 
		}
	};

} // namespace MyGL





