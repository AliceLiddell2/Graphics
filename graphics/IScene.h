
#pragma once

#include "IModel.h"

namespace MyGL
{
	/// Interface 
	///    
	class IScene
	{
	public:
		// constructors and properties

		virtual void InitOpenGL() =0;

		virtual void SetModel(IModel* model) =0;

		virtual void SetViewPort(int W, int H) =0;

		// drawing 

		virtual void Display() =0; 
	};

} // namespace MyGL

