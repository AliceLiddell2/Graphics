
#pragma once

#include "graphics\Common.h"
#include "graphics\ElementBase.h"

namespace MyGL
{

	struct SimplePlane : public ElementBase 
	{
		IElement* innerObject;

		Plane* plane;

		SimplePlane() : innerObject(NULL)
		{
		}

		SimplePlane(IElement* innerObject, const Plane& plane) 
		{
			this->innerObject = innerObject;	
			this->plane = new Plane(plane);
		}

		Plane ReflectionPlane() // final 
		{
			return *plane;
		}

		void Draw(DrawingContext& drwCtx0) const // final 
		{
			DrawingContext drwCtx;
			BeginDraw(drwCtx0, drwCtx);
			//
			ApplyColor(drwCtx.color); 
			//
			glNormal3d(0, 0, 1); 
			//
			if (innerObject) 
			{
				innerObject->Draw(drwCtx); 
			}
			//
			EndDraw();
		}
	};

} // namespace MyGL

