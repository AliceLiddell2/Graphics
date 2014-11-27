
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

		mutable double t;

		// Constructors 

		inline void Construct() 
		{
			// Constants 
			c_wing_s = .56; 
			double c_wing_s2 = .6 * c_wing_s; 
			//
			Add(new Sphere(Vector3d::Zero(), .3), "body");
			IElement* body = GetChild("body");
			//
			body->addToTransformation(Math::ScaleMatrix(.36, 1, .36));
			//
			body->SurfaceColor() = new Color(Color::Chocolate());
			//
			// ---
			// wings
			//
			Group* leftWing = new Group(); 
			Group* rightWing = new Group(); 
			Add(leftWing, "left wing");
			Add(rightWing, "right wing");
			//
			// leftWing = GetChild("left wing");
			// rightWing = GetChild("right wing");
			//
			// left wing 
			//
			Disk* lwD1 = new Disk(Vector3d(-c_wing_s, 0, 0), c_wing_s);
			lwD1->addToTransformation(Math::TranslationMatrix(c_wing_s, 0, 0));
			lwD1->addToTransformation(Math::RotationMatrixZ(-30));
			lwD1->addToTransformation(Math::TranslationMatrix(-c_wing_s, 0, 0));
			lwD1->addToTransformation(Math::ScaleMatrix(1.2, .3, 1));
			//
			Disk* lwD2 = new Disk(Vector3d(-c_wing_s2, 0, 0), c_wing_s2);
			lwD2->addToTransformation(Math::RotationMatrixZ(45));
			lwD2->addToTransformation(Math::ScaleMatrix(1, .6, 1));
			//
			leftWing->Add(lwD1);
			leftWing->Add(lwD2);
			//
			leftWing->SurfaceColor() = new Color(0, 1, 1, 0.6);
			//
			// right wing
			//
			Disk* rwD1 = new Disk(Vector3d( c_wing_s, 0, 0), c_wing_s);
			rwD1->addToTransformation(Math::TranslationMatrix(-c_wing_s, 0, 0));
			rwD1->addToTransformation(Math::RotationMatrixZ(30));
			rwD1->addToTransformation(Math::TranslationMatrix(c_wing_s, 0, 0));
			rwD1->addToTransformation(Math::ScaleMatrix(1.2, .3, 1));
			//
			Disk* rwD2 = new Disk(Vector3d( c_wing_s2, 0, 0), c_wing_s2);
			rwD2->addToTransformation(Math::ScaleMatrix(1, .6, 1));
			rwD2->addToTransformation(Math::RotationMatrixZ(-45));
			//
			rightWing->Add(rwD1);
			rightWing->Add(rwD2);
			//
			rightWing->SurfaceColor() = new Color(0, 1, 1, 0.6);
			//
			// ---
			// common geometry 
			//
			setTransformation(Matrix4d::Identity());
			//addToTransformation(Math::TranslationMatrix(-center()[0], -center()[1], -center()[2]));
			addToTransformation(Math::RotationMatrixZ(alpha)); 
			addToTransformation(Math::RotationMatrixX(26)); 
			//addToTransformation(Math::TranslationMatrix( center()[0],  center()[1],  center()[2]));
		}

		Fly(const Vector3d& initialPos, double alpha) : t(0) 
		{
			this->center() = initialPos;
			this->alpha = alpha;
			this->wings = 0;
			//
			Construct(); 
		}

		// Dynamics

		void Act(double dt) // final 
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
				double dx = 0.00003;
				double dz = 0.1; 
				double dA = 0.33;
				//
				// (*_velocity) += Math::RandomSphericalVector(.1); 
				(*_velocity)[0] = dx * cos(M_PI * alpha / 180.0); 
				(*_velocity)[1] = dx * sin(M_PI * alpha / 180.0); 
				//
				alpha += -dA + 2 * dA * Math::Random01(); 
				//
				z += -dz + 2 * dz * Math::Random01(); 
			}
			//
			t += dt;
			//
			IElement* leftWing = GetChild("left wing");
			IElement* rightWing = GetChild("right wing");
			//
			double beta = 36 * sin(.78 * (t / 1000.0)); 
			//
			leftWing->setTransformation(Math::RotationMatrixY(beta)); 
			rightWing->setTransformation(Math::RotationMatrixY(-beta)); 
			//
			setTransformation(Matrix4d::Identity());
			addToTransformation(Math::RotationMatrixZ(alpha)); 
			addToTransformation(Math::RotationMatrixX(26)); 
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

