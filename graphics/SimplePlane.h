
#pragma once

#include "graphics\ElementBase.h"

namespace MyGL
{

	struct SimplePlane : public ElementBase 
	{
		IElement* innerObject;

		Plane plane;

		SimplePlane() : innerObject(NULL)
		{
		}

		SimplePlane(IElement* innerObject, const Plane& plane) 
		{
			this->innerObject = innerObject;	
			this->plane = plane;
		}

		Plane ReflectionPlane() // final 
		{
			return plane;
		}

		void Draw() const // final 
		{
			BeginDraw();
			//
			if (innerObject) 
				innerObject->Draw(); 
			//
			EndDraw();
		}
	};

} // namespace MyGL

