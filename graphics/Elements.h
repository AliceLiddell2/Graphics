
#pragma once

#include "graphics/IElement.h"
#include "graphics/Group.h"

using namespace std;

namespace MyGL
{
	// ===========================================================================================
	// Primitives

	class TriangleSet : public ElementBase
	{
		// vector<Triangle*> triangles;
	};

	class QuadSet : public ElementBase
	{
	};

	class Surface : public Group
	{
	};

	// ----
	// Special objects

	struct SimplePlane : QuadSet
	{
		double size;
		Vector3d center;
		Vector3d normal;

	};

	struct Box : IElement
	{
		Vector3d center;
		Vector3d normal;

		void Draw() 
		{
			glBegin(GL_QUADS); 
			{
				// ... 
			}
			glEnd();
		}
	};

	struct Disk : ElementBase
	{
		Vector3d center;
		Vector3d normal;

		void Draw() 
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
	};

} // namespace MyGL

