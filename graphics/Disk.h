
#pragma once

#include "graphics/Common.h"
#include "graphics/ElementBase.h"

#define DISK_SLICES 12
#define DISK_STACKS 12

namespace MyGL
{
	struct Disk : ElementBase
	{
		// Vector3d center; // inherited from Movable 
		double innerR;
		double outerR;
		int slices;
		int stacks;

		Vector3d* _normal;

		inline Vector3d& normal() { return *_normal; } 

		Disk(const Vector3d& center, double outerR, double innerR=0) 
			: 
			_normal(new Vector3d(Vector3d(0,0,1))) 
		{
			this->center() = center;
			this->outerR = outerR;
			this->innerR = innerR;
			slices = DISK_SLICES;
			stacks = DISK_STACKS;
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
			gluDisk(Quadric(), innerR, outerR, slices, stacks);
			//
			// glPopMatrix();
			//
			EndDraw(); 
		}
		
		// Properties 

		Plane ReflectionPlane() 
		{
			double d = -(normal()[0]*center()[0] + normal()[1]*center()[1] + normal()[2]*center()[2]); 
			return Vector4d(normal()[0], normal()[1], normal()[2], d); 
		}
		
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

