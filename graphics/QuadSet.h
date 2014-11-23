
#pragma once

#include "graphics/ElementBase.h"
#include "graphics/Group.h"

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

		void Draw() const // final
		{
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
					glVertex3d(v0[0], v0[1], v0[2]);
					glVertex3d(v1[0], v1[1], v1[2]);
					glVertex3d(v2[0], v2[1], v2[2]);
					glVertex3d(v3[0], v3[1], v3[2]);
				}
				glEnd();
			}
		}
	};

} // namespace MyGL

