
#pragma once

#include "graphics/ElementBase.h"

namespace MyGL
{
	class Group : public ElementBase
	{
	public:
		typedef vector<IElement*> ElementContainer;
		typedef map<string,IElement*> ElementSearchT;

	private:
		ElementContainer elements;
		mutable ElementSearchT elementSearch;

	public:
		// content

		inline Group& Add(IElement* element)
		{
			elements.push_back(element);
			return *this;
		}

		inline Group& Add(IElement* element, const string& name) 
		{
			elements.push_back(element);
			elementSearch[name] = element; 
			return *this;
		}

		inline IElement* GetChild(const string& name)
		{
			return elementSearch[name]; 
		}

		//drawing

		void Draw(DrawingContext& drwCtx0) const // final 
		{
			DrawingContext drwCtx;
			BeginDraw(drwCtx0, drwCtx);
			//
			// glPushMatrix();
			//
			// glTranslated(center()[0], center()[1], center()[2]); // ElementBase already does that 
			//
			for (ElementContainer::const_iterator it = elements.begin(); it != elements.end(); ++it)   
			{
				IElement* element = *it; 
				if (element) 
				{
					bool draw = true;
					//
					if (drwCtx.Skip(element->id()))
					{
						draw = false;
					}
					if (element->IsAMirror() && drwCtx.skipMirrors) 
					{
						draw = false; 
					}
					if (element->invisible) 
					{
						draw = false; 
					}
					//
					if (draw) 
					{
						element->Draw(drwCtx); 
					}
				}
			}
			//
			// glPopMatrix();
			//
			EndDraw(); 
		}

		void Act(double dt) //const // final 
		{
			for (ElementContainer::const_iterator it = elements.begin(); it != elements.end(); ++it)   
			{
				IElement* element = *it; 
				if (element) 
				{
					element->Act(dt);
				}
			}
		}
		// Constructors, destructors

		~Group() 
		{
			for (ElementContainer::iterator it = elements.begin(); it != elements.end(); ++it)   
			{
				IElement* element = *it; 
				if (element) delete element; 
			}
		}
	};

} // namespace MyGL

