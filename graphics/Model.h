
#pragma once

#include "graphics\Common.h"
#include "graphics\Elements.h"
#include "graphics\IModel.h"
#include "graphics\ModelLighting.h"

namespace MyGL
{
	/// The Model 
	///    
	class Model : public IModel
		// inner components
		, public ModelLighting 
	{
		Group* group;

	public:
		void Draw(DrawingContext& drwCtx) // final  
		{
			if (group)
			{
				group->Draw(drwCtx);
			}
		}

		virtual ILighting* Lighting() 
		{
			return static_cast<ModelLighting*>(this); 
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
			group = new Group();
			//
			Generate(name); 
		}

		void Generate(const string& name)
		{
			if (name == "summer")
			{
				double a = 3.3;
				double b = 1.8;
				double h = 7.2;
				double lakeW = 20;
				double lakeY = 16;
				double gateY = 4.8;
				//
				// ---
				// Lighting 
				// 
				Lighting()->BackColor() = Color(.7, .7, 1);
				//
				// ---
				// The objects 
				//
				// Ground plane 
				{
					Plane plane(0,0,1,0);
					//
					double z0 = -0.1;
					Vector3d v0(-100,-100,z0), v1(100,-100,z0), v2(100,100,z0), v3(-100,100,z0);
					Vector3d v4(-lakeW,-100,z0), v5(-lakeW,100,z0), v6(lakeW,-100,z0), v7(lakeW,100,z0);
					Vector3d v8(-lakeW,gateY-lakeY,z0), v9(lakeW,gateY-lakeY,z0), v10(lakeW,gateY,z0), v11(-lakeW,gateY,z0);
					//
					// Disk* disk = new Disk(, plane);
					QuadSet* set1 = new QuadSet();
					set1->Add(v0, v4, v5, v3);
					set1->Add(v6, v1, v2, v7);
					set1->Add(v4, v6, v9, v8);
					set1->Add(v11, v10, v7, v5);
					SimplePlane* ground = new SimplePlane(set1, plane);
					//
					ground->SurfaceColor() = new Color(0, 0.5, 0);
					//
					group->Add(ground, "ground");
				}
				//
				// Gate
				{
					Box* box1 = new Box(Vector3d(-a, -b/2, 0), Vector3d(b, b, h-b), true);
					Vector3d pp1(a-b, -b/2, 0);
					Box* box2 = box1->Clone(pp1);
					Box* box3 = new Box(Vector3d(-a, -b/2, h-b), Vector3d(2*a, b, b), true);
					//
					Group* gate = new Group();
					gate->Add(box1).Add(box2).Add(box3);
					//
					gate->SurfaceColor() = new Color(0.5, 0, 0);
					//
					gate->setTransformation(Math::TranslationMatrix(0, gateY, 0)); 
					//
					group->Add(gate); 
				}
				//
				// Lake
				{
					Plane plane(0,0,1,0);
					//
					double z0 = 0;
					Vector3d v0(-20,-16,z0), v1(20,-16,z0), v2(20,-b/2,z0), v3(-20,-b/2,z0);
					//
					// Disk* disk = new Disk(, plane);
					QuadSet* set1 = new QuadSet();
					set1->Add(v0, v1, v2, v3);
					SimplePlane* lake = new SimplePlane(set1, plane);
					//
					lake->SurfaceColor() = new Color(0, 0, 1, .5);
					lake->IsAMirror() = true;
					//
					lake->addToTransformation(Math::TranslationMatrix(0, gateY, 0)); 
					//
					group->Add(lake, "lake");
				}
				//
				// Water flowers
				{
				}
				//
				// Flies
				{
					for (int k = 0; k < 3; k++)
					{
						Vector3d c1 = Math::RandomDiskVector(12);
						c1[1] = c1[1] + 3;
						c1[2] = 3.6; // z-coordinate 
						group->Add(new Fly(c1, Math::RandomAngle())); 
					}
				}
			}
		}

		inline IElement* Lake() const 
		{
			return group->GetChild("lake"); 
		}

		inline IElement* Ground() const 
		{
			return group->GetChild("ground"); 
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

