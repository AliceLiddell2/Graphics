
#pragma once

#include <vector>

#include "graphics/ElementBase.h"

namespace MyGL
{
	class Group : public ElementBase
	{
	public:
		typedef vector<IElement*> ElementContainer;

	private:
		ElementContainer elements;

	public:
		void Draw() // final 
		{
			for (ElementContainer::iterator it = elements.begin(); it != elements.end(); ++it)
			{
				IElement* element = *it; 
				if (element) element->Draw(); 
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

