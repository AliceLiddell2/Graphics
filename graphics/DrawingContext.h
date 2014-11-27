
#pragma once

#include "graphics\Common.h"

namespace MyGL
{
	/// Structure keeping object attributes for hierarchial drawing 
	///    
	struct DrawingContext 
	{
		Color* color;

		GLuint textureId; 

		GLfloat front_mat_shininess[1]; // = {60.0f};
		GLfloat front_mat_specular[4]; // = {0.2f, 0.2f, 0.2f, 1.0f};
		GLfloat front_mat_diffuse[4]; // = {0.5f, 0.28f, 0.38f, 1.0f};

		int skipElementId; 

		bool skipMirrors; 



		DrawingContext() : color(NULL), textureId(NO_TEXTURE)
			, skipElementId(-1)    
			, skipMirrors(false) 
		{
			front_mat_shininess[0] = 60.0f;
			front_mat_specular[0] = front_mat_specular[1] = front_mat_specular[2] = 0.6;
			front_mat_specular[3] = 1;
			front_mat_diffuse[0] = front_mat_diffuse[1] = front_mat_diffuse[2] = 0.5;
			front_mat_diffuse[3] = 1;
		}

		inline void Clone(DrawingContext& newCtx) // newCtx must be empty 
		{
			if (color) 
			{
				newCtx.color = new Color(*color); 
			}
			//
			newCtx.textureId = textureId; 
			//
			newCtx.skipElementId = skipElementId; 
			newCtx.skipMirrors = skipMirrors; 
		}

		inline bool Skip(int id) const 
		{
			if (skipElementId < 0) return false; 
			//
			return skipElementId == id; 
		}
	};

} // namespace MyGL

