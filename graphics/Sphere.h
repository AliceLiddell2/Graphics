
#pragma once

#include "graphics/ElementBase.h"

namespace MyGL
{
	struct Sphere : ElementBase 
	{
		Vector3d center;
		double r;

		void Draw() const 
		{
			double x0 = center[0];
			double y0 = center[1];
			double z0 = center[2];
			//
		}
	};

} // namespace MyGL

