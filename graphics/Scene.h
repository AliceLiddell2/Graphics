
#pragma once

#include "graphics\Common.h"
#include "graphics\IModel.h"
#include "graphics\IScene.h"

using namespace Eigen;

namespace MyGL
{
	/// Compoment BaseScene (abstract)
	///    
	class BaseScene : public IScene
	{
	protected:
		IModel* model;

		int W;
		int H;

		double ratio;

	public:
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
		Scene3D() : upDirection(0, 0, 1), cameraLocation(-2,2,2)
		{
		}

		// Settings

		void InitOpenGL()
		{
			LoadGLTextures();
			glEnable(GL_TEXTURE_2D);
			glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
			glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
			glClearDepth(1.0f);									// Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
			glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
			ShowCursor(FALSE);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

			glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
			glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
			glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
			glEnable(GL_LIGHT1);								// Enable Light One

			glColor4f(1.0f, 1.0f, 1.0f, 0.5);					// Full Brightness.  50% Alpha
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
		}

		void SetViewPort(int W, int H) // final method 
		{
			RememberViewPort(W, H);
		}

		void StartDrawing()
		{
			//
			// ----
			// Projection space
			//
			// Reset the coordinate system before modifying
			//
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//	
			// Set the viewport to be the entire window
			glViewport(0, 0, W, H);
			//
			// Set the clipping volume
			//
			gluPerspective(80, ratio, 1, 200);
			//
			// ----
			// Model coordinate space
			//
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(cameraLocation[0], cameraLocation[1], cameraLocation[2],			// eye
					  0, 0, 0,			// target
					  upDirection[0], upDirection[1], upDirection[2]		// up direction 
					  );
		}

		// Drawing

		void Display() // final method 
		{
			StartDrawing();
			//
			// Drawing objects
			//
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			//
			if (model)
			{
				model->Draw();
			}
			//
			// ----
			// Test
			//
			if (true)
			{
				glPushMatrix();
				//glTranslatef ( 0.0, 0.0, z );
				glRotatef ( xrot, 1.0, 0.0, 0.0 );
				glRotatef ( yrot, 0.0, 1.0, 0.0 );


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
			}
		}

		// Interactivity

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
					light=!light;
					if (!light)
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
			double a = (M_PI * 15) / 180;
			Matrix3d R = Matrix3d::Identity();
			R(0,0) = cos(a);
			R(0,1) = -sin(a);
			R(1,0) = sin(a);
			R(1,1) = cos(a);
			//
			cameraLocation = R * cameraLocation; 
			//
			glutPostRedisplay();
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

