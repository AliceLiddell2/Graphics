
#pragma once

#include "graphics\Common.h"
#include "graphics\IModel.h"
#include "graphics\IScene.h"

#include "graphics\Model.h" // TODO: this is a temporary feature! 

#define TEST_1 (true) 

namespace MyGL
{
	/// Component SceneLighting: common lighting
	/// Compoment BaseScene (abstract)
	///    
	class BaseScene : public IScene
	{
	protected:
		IModel* model;

		int W;
		int H;

		double ratio;

		bool enableLighting;

	public:
		BaseScene() : model(NULL), enableLighting(false) 
		{
		}

		void SetModel(IModel* model) // final method 
		{
			this->model = model;
		}

	protected:
		void RememberViewPort(int W, int H) 
		{
			this->W = W;
			this->H = H;
			//
			ratio = (1.0 * W) / H;
		}
	};

	/// Component 
	///    
	class Scene3D : public BaseScene
	{
		Vector3d cameraLocation;
		Vector3d lookAtPoint;
		Vector3d upDirection;

	public:
		Scene3D() : upDirection(0, 0, 1), cameraLocation(0, -12, 6)
		{
		}

		// Settings

		void InitOpenGL()
		{
			LoadGLTextures();
			glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
			//
			// back color 
			//
			Color backColor = model->Lighting()->BackColor();
			double c_r = backColor.Red();
			double c_g = backColor.Green();
			double c_b = backColor.Blue();
			glClearColor(0.5, 0.7, c_b, 1); // backColor.Alpha() 
			//
			// settings 
			//
			glClearDepth(1.0f);									// Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
			glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
			ShowCursor(FALSE);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			//
			glEnable(GL_NORMALIZE); 
			//
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
			//
			// lights 
			//
			/*
			glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
			glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
			glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
			glEnable(GL_LIGHT1);								// Enable Light One

			*/
		}

		void SetViewPort(int W, int H) // final method 
		{
			RememberViewPort(W, H);
		}

		void Lights(double k=1)
		{
			if (!enableLighting) return; 
			// 
			glEnable(GL_LIGHTING);
			glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
			glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
			glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);		// Setup The Diffuse Light
			glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);	// Position The Light
			glColor3f(1.0f, 1.0f, 1.0f);
			glEnable(GL_LIGHT0);								// Enable Light One
			glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
			glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
			glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);		// Setup The Diffuse Light
			glLightfv(GL_LIGHT1, GL_POSITION,LightPosition1);	// Position The Light
			glColor3f(1.0f, 1.0f, 1.0f);
			glEnable(GL_LIGHT1);								// Enable Light One
			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		}

		inline void SetUpCamera(double k=1)
		{
			// ----
			// Projection space
			//
			// Reset the coordinate system before modifying
			//
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//
			glScaled(1, k, 1);
			//	
			// Set the viewport to be the entire window
			//
			glViewport(0, 0, W, H);
			//
			// Set the clipping volume
			//
			gluPerspective(45, ratio, 1, 200);
			//
			// ----
			// Model coordinate space
			//
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity(); 
			//
			gluLookAt(cameraLocation[0], cameraLocation[1], cameraLocation[2],			// eye
					  0, 0, 0,			// target
					  upDirection[0], upDirection[1], upDirection[2]		// up direction 
					  );
		}

		// Drawing

		void Display() // final method 
		{
			// Drawing objects
			//
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			//
			if (model)
			{
				Model* theModel = static_cast<Model*>(model); 
				//
				DrawingContext ctx0;
				ctx0.skipMirrors = true;
				//
				// Stencil
				//
				SetUpCamera();
				//
				Lights();
				//
				{
					glEnable(GL_STENCIL_TEST); 
					//
					glColorMask(0, 0, 0, 0); 
					glDisable(GL_DEPTH_TEST); 
					glStencilFunc(GL_ALWAYS, 1, 1); 
					glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
					//
					glPushMatrix();
					{
						DrawingContext ctxLake;
						theModel->Lake()->Draw(ctxLake);
					}
					glPopMatrix();
					//
					// Reflection
					//
					// StartDrawing();
					glColorMask(1, 1, 1, 1); 
					glEnable(GL_DEPTH_TEST); 
					glStencilFunc(GL_EQUAL, 1, 1);
					glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); 
					//
					// SetUpCamera(-1);
					//
					glPushMatrix();
					{
						glScaled(1, 1, -1);
						//Lights(-1);
						//
						DrawingContext ctx1;
						ctx0.Clone(ctx1);
						ctx1.skipElementId = theModel->Ground()->id(); 
						model->Draw(ctx1);
						if (TEST_1) DrawTestCube(); 
					}
					glPopMatrix();
					//
					glDisable(GL_STENCIL_TEST); // Disable using the stencil buffer   
				}
				{
					glEnable(GL_STENCIL_TEST); 
					//
					glColorMask(0, 0, 0, 0); 
					glDisable(GL_DEPTH_TEST); 
					glStencilFunc(GL_ALWAYS, 1, 1); 
					glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
					//
					glPushMatrix();
					{
						glBegin(GL_QUADS);
						{
							glVertex3d(-3.3, 5.7, 0);
							glVertex3d( 3.3, 5.7, 0);
							glVertex3d( 3.3, 5.7, 7.2);
							glVertex3d(-3.3, 5.7, 7.2);
						}
						glEnd();
					}
					glPopMatrix();
					//
					// Portal 
					//
					// StartDrawing();
					glColorMask(1, 1, 1, 1); 
					glEnable(GL_DEPTH_TEST); 
					glStencilFunc(GL_EQUAL, 1, 1);
					glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); 
					//
					// SetUpCamera(-1);
					//
					glPushMatrix();
					{
						//glScaled(1, 1, -1);
						//Lights(-1);
						//
						//DrawingContext ctx2;
						//model2->Draw(ctx2);
						if (TEST_1) DrawTestCube(); 
					}
					glPopMatrix();
					//
					glDisable(GL_STENCIL_TEST); // Disable using the stencil buffer   
				}
				//
				//
				// ----
				// Main model 
				//
				// StartDrawing();
				//
				// SetUpCamera();
				//
				//ctx0.skipElementId = theModel->Lake()->id(); 
				ctx0.skipMirrors = false;
				model->Draw(ctx0); 
				//if (TEST_1) DrawTestCube(); 
			}
		}

		inline void DrawTestCube()
		{
				glEnable(GL_TEXTURE_2D);
				glColor3f(1.0f, 1.0f, 1.0f);
				glPushMatrix();
				glTranslated( 0, 9, 2  );

				glRotatef ( xrot, 1.0, 0.0, 0.0 );
				glRotatef ( yrot, 0.0, 1.0, 0.0 );

				glColor4f(1.0f, 1.0f, 1.0f, 0.5);					// Full Brightness.  50% Alpha
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency

				glBindTexture ( GL_TEXTURE_2D, texture_id[filter] );

				glBegin ( GL_QUADS );
				// Front Face
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
				// Back Face
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
				// Top Face
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
				// Bottom Face
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
				// Right face
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
				// Left Face
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
				glEnd();
				glPopMatrix();
				glDisable(GL_TEXTURE_2D);
		}









		// ========================================================================================================
		// ***
		// Interactivity

		void OnSpecialKey(int a_keys, int x, int y)
		{
			switch ( a_keys ) 
			{
			case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
				xspeed-=0.01f;
				break;
			case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
				xspeed+=0.01f;
				break;
			case GLUT_KEY_RIGHT:
				{
					double a = (M_PI * 15) / 180;
					Matrix3d R = Matrix3d::Identity();
					R(0,0) = cos(a);
					R(0,1) = -sin(a);
					R(1,0) = sin(a);
					R(1,1) = cos(a);
					cameraLocation = R * cameraLocation; 
					glutPostRedisplay();
				}
				break;
			case GLUT_KEY_LEFT:
				{
					double a = -(M_PI * 15) / 180;
					Matrix3d R = Matrix3d::Identity();
					R(0,0) = cos(a);
					R(0,1) = -sin(a);
					R(1,0) = sin(a);
					R(1,1) = cos(a);
					cameraLocation = R * cameraLocation; 
					glutPostRedisplay();
				}
				break;
			case GLUT_KEY_F1:
				glutFullScreen ();
				break;
			case GLUT_KEY_F2:
				break;
			default:
				break;
			}
		}

		void OnKeyPress(unsigned char key, int x, int y)
		{
  switch ( key ) {
    case 27:        // When Escape Is Pressed...
      exit ( 0 );   // Exit The Program
      break;        // Ready For Next Case
    case 'f':
      fp=TRUE;
      filter+=1;
		if (filter>2)
		{
			filter=0;
      }
    	break;
    case 'l':
    	lp=TRUE;
			enableLighting=!enableLighting;
					if (!enableLighting)
					{
						glDisable(GL_LIGHTING);
					}
					else
					{
						glEnable(GL_LIGHTING);
					}
      break;
    case 'b':
    	bp=TRUE;
		blend = !blend;
		if(blend)
      {
			glEnable(GL_BLEND);			// Turn Blending On
			glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off
		}
		else
		{
			glDisable(GL_BLEND);		// Turn Blending Off
			glEnable(GL_DEPTH_TEST);	// Turn Depth Testing On
		}
      break;

	case 'r':
		{
			yspeed+=0.01f;
			//
			//
			//
			break;
		}
      
    default:        // Now Wrap It Up
      break;
  }
		}

		void OnMouseMove(int screenX, int screenY)
		{
			// TODO: ...
		}

		void OnMouseClick(int screenX, int screenY)
		{
			// TODO: ...
		}

		// =====================================================================================
		// Global data

		inline static Scene3D& MainScene()
		{
			static Scene3D s_MainScene;
			return s_MainScene;
		}
	};

	/// Component 
	///    
	class Scene2D : public BaseScene
	{
		double centerX;
		double centerY;
		double mag;

	public:
		void Display() // final method 
		{
		}

		void SetViewPort(int W, int H) // final method 
		{
			RememberViewPort(W, H);
			//
			// TODO: not implemented 
		}
	};	

} // namespace MyGL

