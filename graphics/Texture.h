
#pragma once

#include "graphics\Common.h"
#include "graphics\ImageLoader.h"

namespace MyGL
{
	class Texture 
	{
	private:
		Image* image;

		string path;

		GLuint textureId;

		Texture(const string& filename) : image(NULL), textureId(0), path(filename) 
		{
			image = Image::loadBMP((const char*)filename.c_str()); 
			if (!image) ThrowException("image == 0"); 
			//
			glGenTextures ( 1, &textureId );
			glBindTexture ( GL_TEXTURE_2D, textureId );
		}
	public:
		GLuint TextureId() const 
		{
			if (!textureId) ThrowException(string("Texture is not bound: ") + path);
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
		Texture& GetTexture(const string& filename) 
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

