
#pragma once

#include <list> 

#include "graphics/Elements.h"
#include "graphics/IModel.h"

namespace MyGL
{
	/// Interface for elementary or compound object 
	///    
	class Model : public IModel
	{
		Group* group;

	public:
		void Draw() // final  
		{
			if (group)
				group->Draw();
		}

		// Constructors

		Model() 
		{
			group = new Group();
		}

		~Model()
		{
			if (group) delete group;
		}


	
		// ---------------------------------------------------
		// Generation

		Model(const string& name)
		{
			Generate(name); 
		}

		void Generate(const string& name)
		{
			if (name == "summer")
			{
				/*
				// Gate
				{
					Group* gate = new Group();
					// gate->color = ...;
					gate->Add(new Box());
					gate->Add(new Box());
					gate->Add(new Box());
					//
					group->Add(gate); 
				}
				//
				// Lake
				{
					// ....
					group->Add(lake);
				}
				//*/
			}
		}











		// =========================================================
		// Model container 

	private:
		typedef map<string, Model*> ModelContainerT;

		inline static ModelContainerT& ModelContainer() 
		{
			static ModelContainerT s_modelContainer;
			return s_modelContainer;
		}

	public:
		inline static Model& GetModel(const string& name)
		{
			ModelContainerT::iterator i = ModelContainer().find(name);
			if (i != ModelContainer().end())
			{
				Model* model = i->second;
				return *model; // TODO: check 0 --> exception 
			}
			else
			{
				Model* model = new Model(name);
				ModelContainer()[name] = model;
				return *model;
			}
		}
	};

} // namespace MyGL

