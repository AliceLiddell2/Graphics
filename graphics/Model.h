
#pragma once

#include <list> 

#include "graphics/Common.h"
#include "graphics/Exception.h"
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
				double a = 3;
				double b = 1;
				double h = 6;
				//
				// Gate
				{
					Box* box1 = new Box(Vector3d(-a, -b/2, 0), Vector3d(b, b, h-b), true);
					Box* box2 = box1->Clone(Vector3d(a-b, -b/2, 0));
					Box* box3 = new Box(Vector3d(-a, -b/2, b-a), Vector3d(2*a, b, b), true);
					//
					Group* gate = new Group();
					// gate->color = ...;
					gate->Add(box1).Add(box2).Add(box3);
					//
					group->Add(gate); 
				}
				//
				// Lake
				{
					Plane plane(0,0,1,0);
					//
					Vector3d v0(-10,-6,0), v1(10,-6,0), v2(10,-b/2,0), v3(-10,-b/2,0);
					//
					// Disk* disk = new Disk(, plane);
					QuadSet* set1 = new QuadSet();
					set1->Add(v0, v1, v2, v3);
					SimplePlane* lake = new SimplePlane(set1, plane);
					lake->IsAMirror() = true;
					//
					group->Add(lake);
				}
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
				if (!model) ThrowException("model == 0"); 
				return *model; 
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

