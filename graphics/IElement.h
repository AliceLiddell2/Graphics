
#pragma once

namespace MyGL
{
	/// Interface for elementary or compound object 
	///    
	class IElement
	{
	public:
		virtual void Draw() =0; 

		virtual bool IsAMirror() =0; 
	};

} // namespace MyGL

