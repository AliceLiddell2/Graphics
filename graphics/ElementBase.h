
#pragma once

#include "graphics/Common.h"
#include "graphics/Color.h"
#include "graphics/Exception.h"
#include "graphics/Texture.h"
#include "graphics/IElement.h"

#define ELEMENT_MAX_ID 1024 * 1024

namespace MyGL
{
	class Movable
	{
	protected:
		Movable() 
			: 
			_center		(new Vector3d(Vector3d::Zero())), 
			_velocity	(new Vector3d(Vector3d::Zero())) 
		{
		}

		mutable Vector3d* _center; 
		mutable Vector3d* _velocity; 

		int _id; 

	public:
		inline Vector3d& center()	{ return *_center; }; 
		inline Vector3d& velocity()	{ return *_velocity; }; 

		inline const Vector3d& center()		const { return *_center; }; 
		inline const Vector3d& velocity()	const { return *_velocity; }; 

		// EIGEN_MAKE_ALIGNED_OPERATOR_NEW // ! deprecated ! 
	};

	class ElementBase : public IElement, public Movable 
	{
	protected:
		// ----
		// Surface and material properties 

		// Principal behaviour flags 

		bool isAMirror;

		// Structural properties 

		int polygonMode;

		// Simple color

		Color* color;

		// Texture 

		Texture* texture;

		double textureMag; 

		// Material 

		double front_mat_shininess[1]; // = {60.0f};
		double front_mat_specular[4]; // = {0.2f, 0.2f, 0.2f, 1.0f};
		double front_mat_diffuse[4]; // = {0.5f, 0.28f, 0.38f, 1.0f};

		// Geometry

		mutable bool applyTransform;

		mutable Matrix4d* transformation; 

	public:
		ElementBase() : 
			// properties 
			isAMirror(false), 
			//
			polygonMode(GL_FILL), 
			color(NULL), 
			texture(NULL), 
			textureMag(1), 
			//
			// transformations
			applyTransform(false), 
			transformation(NULL) 
		{
			_id = Math::RandomInt(ELEMENT_MAX_ID); 
			IElement::AllElements()[_id] = this;  
			//
			invisible = false; 
		}

		virtual int id() const // final 
		{
			return _id;
		}

		virtual Color*& SurfaceColor() { return color; } 

		virtual const Color* SurfaceColor() const { return color; } 

		virtual bool& IsAMirror() { return isAMirror; } 

		bool TextureIsBound() const { return texture != NULL; } 

		virtual void BindTexture(const string& name) // final 
		{
			texture = &( Texture::GetTexture(name) ); 
			// never not call this to postpone texture generation! // return texture->TextureId(); 
		}

		inline double& TextureMag() // final
		{
			return textureMag; 
		}

		virtual Plane ReflectionPlane() const { ThrowException("Reflection plane is undefined for this object"); }   

		virtual void Act(double dt)  {} // default empty stub (must be overriden to create new behaviour) 

		void Move(double dt) const 
		{
			*_center += dt * velocity(); 
		}


		// -------------------------------------------------------------------------------------
		// Constructors, destructors 

		~ElementBase() 
		{
			if (color) delete color; 
			if (transformation) delete transformation;
		}

		// -------------------------------------------------------------------------------------
		// Geometry and drawing

		void setTransformation(const Matrix4d& m) const // final 
		{
			applyTransform = true; 
			if (!transformation)
			{
				transformation = new Matrix4d(m); 
			}
			else
			{
				*transformation = m; 
			}
		}

		void addToTransformation(const Matrix4d& m) const // final 
		{
			applyTransform = true; 
			if (!transformation)
			{
				transformation = new Matrix4d(m); 
			}
			else
			{
				*transformation *= m; 
			}
		}

		Matrix4d getTransformation() const // final 
		{
			if (transformation)
			{
				return *transformation; 
			}
			else
			{
				return Matrix4d::Identity(); 
			}
		}

	protected:
		inline void BeginDraw(DrawingContext& parentCtx, DrawingContext& drwCtx) const
		{
			parentCtx.Clone(drwCtx);
			UpdateDrawingContext(drwCtx);
			//
			glPushMatrix();
			//
			glTranslated(center()[0], center()[1], center()[2]);
			//
			if (applyTransform && transformation)
			{
				double* m = transformation->data(); 
				glMultMatrixd(m);
			}
			//
			// Very common properties 
			//
			glPolygonMode(GL_FRONT_AND_BACK, polygonMode); 
			//
			if (color) 
			{
				if (color->Alpha() < NONTRANSPARENT_ALPHA)
				{
					glEnable(GL_BLEND);
				}
			}
		}

		inline void EndDraw() const
		{
			//if (applyTransform && transformation) 
			//{
			//}
			//
			glPopMatrix();
			//
			if (color) 
			{
				if (color->Alpha() < NONTRANSPARENT_ALPHA)
				{
					glDisable(GL_BLEND);
				}
			}
		}



		// Hierarchial drawing context 

		inline void UpdateDrawingContext(DrawingContext& drwCtx) const 
		{
			if (SurfaceColor())
			{
				drwCtx.color = new Color(*SurfaceColor());
			}
			if (TextureIsBound())
			{
				drwCtx.textureId = texture->TextureId(); 
			}
		}

		// Colors, materials, textures

		inline void ApplyColor(const Color* color) const 
		{
			if (!color) 
				return;		// nothing to do
			//
			// color->Output(); 
			//
			glColor4d(color->Red(), color->Green(), color->Blue(), color->Alpha());
			GLfloat front_mat_shininess[1]; // = {60.0f};
			GLfloat front_mat_specular[4]; // = {0.2f, 0.2f, 0.2f, 1.0f};
			GLfloat front_mat_diffuse[4]; // = {0.5f, 0.28f, 0.38f, 1.0f};
			front_mat_shininess[0] = 60;
			for (int j = 0; j < 4; j++)
			{
				front_mat_specular[j] = (*color)[j]; 
				front_mat_diffuse[j] = (*color)[j]; 
			}
			glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, front_mat_diffuse); 
			glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, front_mat_specular); 
			glMaterialfv (GL_FRONT_AND_BACK, GL_SHININESS, front_mat_shininess); 
		}



	};

} // namespace MyGL

