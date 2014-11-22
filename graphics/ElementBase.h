
#pragma once

#include "graphics/Common.h"
#include "graphics/IElement.h"

namespace MyGL
{
	class ElementBase
	{
	protected:
		Vector4d color;

	public:
		virtual bool IsAMirror() {} // default stub 
	};

} // namespace MyGL

