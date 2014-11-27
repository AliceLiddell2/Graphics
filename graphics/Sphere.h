
#pragma once

#include "graphics\Common.h"
#include "graphics\ElementBase.h"

#define SPHERE_SLICES 12
#define SPHERE_STACKS 12

namespace MyGL
{
	struct Sphere : ElementBase 
	{
		// Vector3d center; // inherited from Movable 
		double radius;
		int slices;
		int stacks;

		// Constructors 

		Sphere(const Vector3d& center, double radius) 
		{
			this->center() = center;
			this->radius = radius;
			this->slices = SPHERE_SLICES;
			this->stacks = SPHERE_STACKS;
		}

		// Drawing

		void Draw(DrawingContext& drwCtx0) const 
		{
			DrawingContext drwCtx;
			BeginDraw(drwCtx0, drwCtx);
			//
			ApplyColor(drwCtx.color); 
			//
			// glPushMatrix();
			//
			// glTranslated(center()[0], center()[1], center()[2]);
			//
			gluSphere(Quadric(), radius, slices, stacks);
			//
			// glPopMatrix();
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

