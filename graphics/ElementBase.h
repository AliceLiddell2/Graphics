
#pragma once

#include "graphics/Common.h"
#include "graphics/Color.h"
#include "graphics/Exception.h"
#include "graphics/Texture.h"
#include "graphics/IElement.h"

namespace MyGL
{
	class ElementBase : public IElement
	{
	protected:
		// Surface and material properties 

		Color color;

		bool isAMirror;

		Texture* texture;

		// Geometry

		bool applyTransform;

		Matrix4d transformation; 

	public:
		ElementBase() : color(Color::White()), isAMirror(false), texture(NULL), applyTransform(false) 
		{
		}

		virtual Color& SurfaceColor() { return color; } 

		virtual bool& IsAMirror() { return isAMirror; } 

		virtual Plane ReflectionPlane() { ThrowException("Reflection plane is undefined for this object"); } 


		// Geometry and drawing
	protected:
		inline void BeginDraw() const
		{
			if (applyTransform)
			{
				glPushMatrix();
				glMultMatrixd(transformation.data());
			}
		}

		inline void EndDraw() const
		{
			if (applyTransform)
				glPopMatrix();
		}
	};

} // namespace MyGL

