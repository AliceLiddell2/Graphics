
#pragma once

#include "graphics\Common.h"
#include "graphics\ElementBase.h"
#include "graphics\Group.h"

using namespace std;

namespace MyGL
{
	struct Box : ElementBase
	{
	public:
		// constructors 

		Box(const Vector3d& start, const Vector3d& size, bool absCoord=true, const Matrix4d* trans=NULL) 
			: 
			_start	(new Vector3d()), 
			_size	(new Vector3d()) 
		{
			CreateBox(start, size, absCoord, trans); 
		}

	protected:
		inline void CreateBox(const Vector3d& start, const Vector3d& size, bool absCoord=true, const Matrix4d* trans=NULL) 
		{
			applyTransform = !absCoord;
			if (!absCoord)
			{
				if (trans) *transformation = *trans; 
			}
			this->start() = start;
			this->size() = size;
		}

		// attributes 

		Vector3d* _start;
		Vector3d* _size;

		inline Vector3d& start()	{ return *_start; }
		inline Vector3d& size()		{ return *_size; }

		inline const Vector3d& start()	const { return *_start; }
		inline const Vector3d& size()	const { return *_size; }

		// EIGEN_MAKE_ALIGNED_OPERATOR_NEW // ! deprecated ! 



	public:
		// --------------------------------------------------------------------------------------
		// drawing

		void Draw(DrawingContext& drwCtx0) const 
		{
			DrawingContext drwCtx;
			BeginDraw(drwCtx0, drwCtx);
			//
			//glMaterialfv (GL_FRONT, GL_DIFFUSE, drwCtx.front_mat_diffuse); 
			//glMaterialfv (GL_FRONT, GL_SPECULAR, drwCtx.front_mat_specular); 
			//glMaterialfv (GL_FRONT, GL_SHININESS, drwCtx.front_mat_shininess); 
			//
			double x0 = start()[0];
			double y0 = start()[1];
			double z0 = start()[2];
			double x1 = x0 + size()[0];			double dx = x1 - x0;
			double y1 = y0 + size()[1];			double dy = y1 - y0;
			double z1 = z0 + size()[2];			double dz = z1 - z0;
			//
			GLuint texId = drwCtx.textureId; 
			bool b = (texId != NO_TEXTURE); 
			//
			if (b)
			{
				glDisable(GL_COLOR_MATERIAL); 
				//
				glEnable(GL_TEXTURE_2D);
				//glColor4f(1.0f, 1.0f, 1.0f, 0.5);					// Full Brightness  (50% Alpha)
				//glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
				//
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glColor3f(1, 1, 1); 
				//
				glBindTexture(GL_TEXTURE_2D, texId); 
			}
			else
			{
				ApplyColor(drwCtx.color); 
			}
			//
			glBegin(GL_QUADS); 
			{
				// base 
				//
				glNormal3d(0,0,-1); 
				//
				if (b) glTexCoord2f( 0,  0);		glVertex3d(x0,y0,z0);
				if (b) glTexCoord2f( 0, dy);		glVertex3d(x0,y1,z0);
				if (b) glTexCoord2f(dx, dy);		glVertex3d(x1,y1,z0);
				if (b) glTexCoord2f(dx,  0);		glVertex3d(x1,y0,z0);
				//
				//
				// roof 
				//
				glNormal3d(0,0,1);
				//
				if (b) glTexCoord2f( 0,  0);		glVertex3d(x0,y0,z1);
				if (b) glTexCoord2f( 0, dy);		glVertex3d(x0,y1,z1);
				if (b) glTexCoord2f(dx, dy);		glVertex3d(x1,y1,z1);
				if (b) glTexCoord2f(dx,  0);		glVertex3d(x1,y0,z1);
				//
				//
				// right 
				//
				glNormal3d(1,0,0);
				//
				if (b) glTexCoord2f( 0,  0);		glVertex3d(x1,y0,z0);
				if (b) glTexCoord2f(dy,  0);		glVertex3d(x1,y1,z0);
				if (b) glTexCoord2f(dy, dz);		glVertex3d(x1,y1,z1);
				if (b) glTexCoord2f( 0, dz);		glVertex3d(x1,y0,z1);
				//
				//
				// left
				//
				glNormal3d(-1,0,0);
				//
				if (b) glTexCoord2f(dy,  0);		glVertex3d(x0,y1,z0);
				if (b) glTexCoord2f( 0,  0);		glVertex3d(x0,y0,z0);
				if (b) glTexCoord2f( 0, dz);		glVertex3d(x0,y0,z1);
				if (b) glTexCoord2f(dy, dz);		glVertex3d(x0,y1,z1);
				//
				//
				// back 
				//
				glNormal3d(0,1,0);
				//
				if (b) glTexCoord2f( 0,  0);		glVertex3d(x0,y1,z0);
				if (b) glTexCoord2f( 0, dz);		glVertex3d(x0,y1,z1);
				if (b) glTexCoord2f(dx, dz);		glVertex3d(x1,y1,z1);
				if (b) glTexCoord2f(dx,  0);		glVertex3d(x1,y1,z0);
				//
				//
				// front 
				//
				glNormal3d(0,-1,0);
				//
				if (b) glTexCoord2f( 0,  0);		glVertex3d(x0,y0,z0);
				if (b) glTexCoord2f(dx,  0);		glVertex3d(x1,y0,z0);
				if (b) glTexCoord2f(dx, dz);		glVertex3d(x1,y0,z1);
				if (b) glTexCoord2f( 0, dz);		glVertex3d(x0,y0,z1);
			}
			glEnd();
			//
			if (b)
			{
				glDisable(GL_TEXTURE_2D);
			}
			//
			EndDraw();
		}


		// --------------------------------------------
		// Misc

		Box* Clone(const Matrix4d& newTrans) const // new reference 
		{
			Box* box = new Box(start(), size(), false, &newTrans);
		}

		Box* Clone(const Vector3d& newStart) const // new reference 
		{
			Box* box = new Box(newStart, size(), this->applyTransform, this->transformation);
			return box;
		}
	};

} // namespace MyGL

