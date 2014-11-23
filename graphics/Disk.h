
#pragma once

#include "graphics/ElementBase.h"

namespace MyGL
{
	struct Disk : ElementBase
	{
		Vector3d center;
		Vector3d normal;

		// Drawing

		void Draw() const 
		{
			glPushMatrix();
			//
			glTranslated(center[0], center[1], center[2]);
			//
			glBegin(GL_TRIANGLES); // GL_TRIANGLE_STRIP
			{
				// ... 
			}
			glEnd();
			//
			glPopMatrix();
		}
		
		// Properties 

		Plane ReflectionPlane() 
		{
			double d = -(normal[0]*center[0] + normal[1]*center[1] + normal[2]*center[2]); 
			return Vector4d(normal[0], normal[1], normal[2], d); 
		}
	};

} // namespace MyGL

