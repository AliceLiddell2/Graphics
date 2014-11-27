
#pragma once

#include "graphics\Common.h"
#include "graphics\ElementBase.h"
#include "graphics\Group.h"

using namespace std;

namespace MyGL
{

	class QuadSet : public ElementBase
	{
		vector<Vector3d> data;

	public:
		inline int size() const
		{
			return data.size() / 4;
		}

		inline QuadSet& Add(
			const Vector3d& v0, 
			const Vector3d& v1, 
			const Vector3d& v2, 
			const Vector3d& v3)
		{
			data.push_back(v0);
			data.push_back(v1);
			data.push_back(v2);
			data.push_back(v3);
			//
			return *this;
		}

		void Draw(DrawingContext& drwCtx0) const // final
		{
			DrawingContext drwCtx;
			BeginDraw(drwCtx0, drwCtx);
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
			int n = size();
			//		
			for (int i = 0; i < n; i++)
			{
				const Vector3d& v0 = data[4*i];
				const Vector3d& v1 = data[4*i+1];
				const Vector3d& v2 = data[4*i+2];
				const Vector3d& v3 = data[4*i+3];
				//
				glBegin(GL_QUADS);
				{
					double m = const_cast<QuadSet*>(this)->TextureMag(); 
					//
					double x0 = v0[0] / m; 
					double x1 = v2[0] / m; 
					double y0 = v0[1] / m; 
					double y1 = v2[1] / m; 
					//
					if (b) glTexCoord2f(x0, y0);		glVertex3d(v0[0], v0[1], v0[2]);
					if (b) glTexCoord2f(x1, y0);		glVertex3d(v1[0], v1[1], v1[2]);
					if (b) glTexCoord2f(x1, y1);		glVertex3d(v2[0], v2[1], v2[2]);
					if (b) glTexCoord2f(x0, y1);		glVertex3d(v3[0], v3[1], v3[2]);
				}
				glEnd();
			}
			//
			if (b)
			{
				glDisable(GL_TEXTURE_2D);
			}
			//
			EndDraw(); 
		}
	};

} // namespace MyGL

