
#pragma once

#include "graphics\Common.h" 
#include "graphics\DrawingContext.h" 
#include "graphics\ILighting.h" 

namespace MyGL
{
	/// Interface 
	///    
	class IModel 
	{
	public:
		virtual void Draw(DrawingContext& drwCtx) =0; 

		virtual ILighting* Lighting() =0; 

		virtual void Act(double dt) =0; 
	};

} // namespace MyGL

