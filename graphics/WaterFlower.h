
#pragma once

#include "graphics/Common.h"
#include "graphics/Sphere.h"		// including the entire Elements.h is prohibited (!) 
#include "graphics/WaterFlowerLeaf.h" 
#include "graphics/Group.h"

#define CYLINDER_SLICES 12
#define CYLINDER_STACKS 12

namespace MyGL
{
	struct WaterFlower : public Group 
	{
		double radius;

		double alpha;

		mutable double t;

		// Constructors 

		inline void Construct() 
		{
			Vector3d p1 = Vector3d::Zero(); 
			p1[2] = p1[2] + 0.5 * radius; // z-coordinate 
			Sphere* ball = new Sphere(p1, radius); 
			//
			//char s[1024];
			//sprintf(s, "color(%02f, %02f, %02f)", p1[0], p1[1], p1[2]);
			//cout << s << endl; 
			//
			ball->SurfaceColor() = new Color(Color::LightGoldenrodYellow());
			//
			Add(ball, "sphere"); 
			//
			// leafs 
			//
			for (int k = 0; k < 4; k++)
			{
				IElement* leaf = new WaterFlowerLeaf(Vector3d::Zero(), 3*radius, 90); 
				leaf->addToTransformation(Math::RotationMatrixZ(90*k));
				Add(leaf); 
			}
			//
			/*
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
			*/
		}

		WaterFlower(const Vector3d& initialPos, double radius) : t(0), alpha(0)   
		{
			this->center() = initialPos;
			this->radius = radius;
			//
			Construct(); 
		}

		// Dynamics

		void Act(double dt) // final 
		{
			Move(dt);
			//
			t += dt;
			//
			alpha = .1 * (t / 1000.0); 
			//
			setTransformation(Matrix4d::Identity());
			addToTransformation(Math::RotationMatrixZ(alpha)); 
		} 

		// Drawing

		// void Draw(DrawingContext drwCtx0) const // Inherited from Group! 

	};

} // namespace MyGL

