
#pragma once

#include "graphics/Common.h"
#include "graphics/ElementBase.h"

#define CYLINDER_SLICES 12
#define CYLINDER_STACKS 12

namespace MyGL
{
	struct Cylinder : ElementBase
	{
		// Vector3d center; // inherited from Movable 
		double baseR;
		double topR;
		double h;
		int slices;
		int stacks;

		// Constructors 

		Cylinder (const Vector3d& center, double baseR, double topR, double h) 
		{
			this->center = center;
			this->h = h;
			this->baseR = baseR;
			this->topR = topR;
			this->slices = CYLINDER_SLICES;
			this->stacks = CYLINDER_STACKS;
		}

		// Drawing

		void Draw(DrawingContext drwCtx0) const 
		{
			DrawingContext drwCtx;
			BeginDraw(drwCtx0, drwCtx);
			//
			ApplyColor(drwCtx.color); 
			//
			glPushMatrix();
			//
			glTranslated(center[0], center[1], center[2]);
			//
			gluCylinder(Quadric(), baseR, topR, h, slices, stacks);
			//
			glPopMatrix();
			//
			EndDraw(); 
		}
		
		// Properties 

		// ---- 
		// Static data 

		inline static GLUquadric* Quadric() 
		{
			static GLUquadric* s_Quadric = NULL; 
			//
			if (!s_Quadric)
			{
				s_Quadric = gluNewQuadric(); 
			}
			//
			return s_Quadric;
		}
	};

} // namespace MyGL

