
#pragma once

#include "graphics/Common.h"
#include "graphics/ElementBase.h"

#define CYLINDER_SLICES 12
#define CYLINDER_STACKS 12

namespace MyGL
{
	struct WaterFlowerLeaf : public ElementBase  
	{
		double L;

		double angle;

		// Constructors 

		WaterFlowerLeaf(const Vector3d& initialPos, double L, double angle)   
		{
			this->center() = initialPos;
			this->L = L;
			this->angle = angle;
		}

		// Drawing

		void Draw(DrawingContext& drwCtx0) const // final 
		{
			int n = 7;
			int m = 5;
			//
			Color c0 = Color::PaleGreen(); 
			Color c1 = Color::SeaGreen(); 
			//
			glPushMatrix(); 
			//
			if (transformation)
			{
				double* matrix = transformation->data(); 
				glMultMatrixd(matrix); 
			}
			//
			for (int mode = 0; mode <= 1; mode++)
			{
				if (mode == 0) 
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
					glColor3d(c0.Red(), c0.Green(), c0.Blue()); 
				}
				else if (mode == 1)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
					glColor3d(c1.Red(), c1.Green(), c1.Blue()); 
				}
				//
				glBegin(GL_QUADS);
				{
					double h = (0.15 + 0.1*mode) * L;
					//
					for (int i = 0; i < n; i++)
					{
						double y0 = double(L * i) / n;
						double y1 = double(L * (i+1)) / n;
						//
						double s0 = (L/M_PI) * sin((double(i)/n) * M_PI) * (angle / 90); 
						double s1 = (L/M_PI) * sin((double(i+1)/n) * M_PI) * (angle / 90); 
						//
						double z0 = h * (1 - cos((double(i)/n) * 1.3 * M_PI));
						double z1 = h * (1 - cos((double(i+1)/n) * 1.3 * M_PI));
						//
						for (int j = 0; j < m; j++) 
						{
							double x0a = -s0 + 2 * (s0 * j) / m; 
							double x1a = -s0 + 2 * (s0 * (j+1)) / m; 
							double x0b = -s1 + 2 * (s1 * j) / m; 
							double x1b = -s1 + 2 * (s1 * (j+1)) / m; 
							//
							glVertex3d(x0a, y0, z0); 
							glVertex3d(x1a, y0, z0); 
							glVertex3d(x1b, y1, z1); 
							glVertex3d(x0b, y1, z1); 
						}
					}
				}
				glEnd();
			}
			//
			glPopMatrix(); 
		}

	};

} // namespace MyGL

