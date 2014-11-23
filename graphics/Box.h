
#pragma once

#include "graphics/ElementBase.h"
#include "graphics/Group.h"

using namespace std;

namespace MyGL
{
	struct Box : ElementBase
	{
		// constructors 

		explicit Box(const Vector3d& start, const Vector3d& size, bool absCoord=true, const Matrix4d* trans=NULL) 
		{
			applyTransform = !absCoord;
			if (!absCoord)
			{
				if (trans) transformation = *trans;
			}
			this->start = start;
			this->size = size;
		}

		// attributes 

		Vector3d start;
		Vector3d size;

		// drawing

		void Draw() const 
		{
			BeginDraw();
			//
			double x0 = start[0];
			double y0 = start[1];
			double z0 = start[2];
			double x1 = x0 + size[0];
			double y1 = y0 + size[1];
			double z1 = z0 + size[2];
			//
			glBegin(GL_QUADS); 
			{
				glNormal3d(0,0,-1);
				//
				glVertex3d(x0,y0,z0);
				glVertex3d(x0,y1,z0);
				glVertex3d(x1,y1,z0);
				glVertex3d(x1,y0,z0);
				//
				//
				glNormal3d(0,0,1);
				//
				glVertex3d(x0,y0,z0);
				glVertex3d(x0,y1,z0);
				glVertex3d(x1,y1,z0);
				glVertex3d(x1,y0,z0);
				//
				// ... 
			}
			glEnd();
			//
			EndDraw();
		}


		// --------------------------------------------
		// Misc

		Box* Clone(const Matrix4d& newTrans) // new reference 
		{
			return new Box(this->start, this->size, false, &newTrans);
		}

		Box* Clone(const Vector3d& newStart) // new reference 
		{
			Box* box = new Box(newStart, this->size, this->applyTransform, &(this->transformation));
			return box;
		}
	};

} // namespace MyGL

