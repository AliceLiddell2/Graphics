
#pragma once

#include "graphics\Common.h"
#include "graphics\ImageLoader.h"

namespace MyGL
{
	class Texture 
	{
	private:
		string path;

		mutable Image* image;

		mutable GLuint textureId;

		inline void CreateTexture() const 
		{
			if (textureId > 0) return;
			//
			image = Image::loadBMP((const char*)path.c_str()); 
			if (!image) 
				ThrowException("image == 0"); 
			//
			glEnable(GL_TEXTURE);
			glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
			glGenTextures ( 1, &textureId );
			glBindTexture ( GL_TEXTURE_2D, textureId );
			//
			glTexImage2D(GL_TEXTURE_2D, 
				0, 
				GL_RGB, 
				image->width, image->height, 
				0, 
				GL_BGR, 
				GL_UNSIGNED_BYTE, 
				image->pixels);
			//
			glDisable(GL_TEXTURE);

		}

		Texture(const string& filename) : image(NULL), textureId(NO_TEXTURE), path(filename) 
		{
			textureId = NO_TEXTURE; 
		}

	public:
		GLuint TextureId() const 
		{
			CreateTexture();
			//
			if (textureId == NO_TEXTURE) ThrowException(string("Texture is not bound: ") + path);
			//
			return textureId;
		}

	private:
		// =====================================================================
		// Containers

		typedef map<string,Texture*> TextureContainerT;

		inline static TextureContainerT& TextureContainer()
		{
			static TextureContainerT s_TextureContainer;
			return s_TextureContainer;
		}

	public:
		inline static Texture& GetTexture(const string& filename) 
		{
			TextureContainerT::iterator i = TextureContainer().find(filename);
			if (i != TextureContainer().end())
			{
				Texture* t = i->second;
				if (!t) ThrowException("texture == 0");
				return *t; 
			}
			else
			{
				Texture* t = new Texture(filename);
				TextureContainer()[filename] = t;
				return *t;
			}
		}
	};

} // namespace MyGL

