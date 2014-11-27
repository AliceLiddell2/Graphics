
#pragma once

#include "graphics\Common.h"
#include "graphics\DrawingContext.h"

namespace MyGL
{
	/// Interface for elementary or compound object 
	///    
	class IElement
	{
	public:
		// Drawing

		virtual void Draw(DrawingContext& drwCtx) const =0; 

		// Geometry

		virtual void setTransformation(const Matrix4d& m) const =0;

		virtual void addToTransformation(const Matrix4d& m) const =0;

		virtual Matrix4d getTransformation() const =0;

		// Dynamics and interactivity 

		virtual void Act(double dt) =0; 

		// Surface properties

		virtual Color*& SurfaceColor() =0;

		virtual const Color* SurfaceColor() const =0;

		virtual void BindTexture(const string& name) =0; 

		virtual double& TextureMag() =0;

		virtual bool& IsAMirror() =0; 

		virtual Plane ReflectionPlane() const =0;

		// Special 

		virtual int id() const =0;

		bool invisible;



		// ----
		// Special global properties 

		inline static map<int,IElement*>& AllElements() 
		{
			static map<int,IElement*> s_AllElements;
			return s_AllElements; 
		}
	};

} // namespace MyGL

