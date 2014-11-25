
#pragma once

#include "graphics/Common.h"
#include "graphics/ElementBase.h"

#define CYLINDER_SLICES 12
#define CYLINDER_STACKS 12

namespace MyGL
{
	struct Fly : public Group 
	{
		double c_wing_s;

		double alpha;
		double wings;

		// Constructors 

		inline void Construct() 
		{
			// Constants 
			c_wing_s = .56; 
			//
			Add(new Sphere(Vector3d::Zero(), .3), "body");
			Add(new Disk(Vector3d(-c_wing_s, 0, 0), c_wing_s), "left wing");
			Add(new Disk(Vector3d( c_wing_s, 0, 0), c_wing_s), "right wing");
			//
			IElement* body = GetChild("body");
			IElement* leftWing = GetChild("left wing");
			IElement* rightWing = GetChild("right wing");
			//
			body->SurfaceColor() = new Color(1, 0, 1);
			leftWing->SurfaceColor() = new Color(0, 1, 1, 0.6);
			rightWing->SurfaceColor() = new Color(0, 1, 1, 0.6);
		}

		Fly(const Vector3d& initialPos, double alpha) 
		{
			this->center() = initialPos;
			this->alpha = alpha;
			this->wings = 0;
			//
			Construct(); 
		}

		// Dynamics

		void Act(double dt) const // final 
		{
			Move(dt);
			//
			double z = center()[2];
			//
			if (z < 0.3) 
			{
				(*_velocity)[2] = -velocity()[2];
			}
			else
			{
				(*_velocity) += Math::RandomSphericalVector(.1); 
			}
		}

		// Drawing

		// void Draw(DrawingContext drwCtx0) const // Inherited from Group! 
		
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

