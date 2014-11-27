
#pragma once

#include "graphics\Common.h"
#include "graphics\IModel.h"
#include "graphics\IScene.h"

#include "graphics\Model.h" // TODO: this is a temporary feature! 

#pragma comment(lib, "glew32.lib" )

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



	// ==============================================================================================
	// 3D scene 

	/// Component 
	///    
	class Scene3D : public BaseScene
	{
		Vector4d cameraLocation;
		Vector3d lookAtPoint;
		Vector3d upDirection;

	public:
		Scene3D() : upDirection(0, 0, 1), cameraLocation(0, -18, 7.5, 1), lookAtPoint(0, 0, 2), 
					reflection(0), rboId(0)   
		{
			texSize = 1024;
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
			////// InitReflectionFBO(); 
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
			gluLookAt(cameraLocation[0], cameraLocation[1], cameraLocation[2],	// eye (camera) 
					  lookAtPoint[0], lookAtPoint[1], lookAtPoint[2],			// target
					  upDirection[0], upDirection[1], upDirection[2]			// up direction 
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
				// RenderReflection();
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
						Matrix4d m;
						IElement* lake = theModel->Lake(&m); 
						glMultMatrixd(m.data()); 
						lake->Draw(ctxLake);
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
						Matrix4d m;
						IElement* lake = theModel->Lake(&m); 
						glMultMatrixd(m.data()); 
						//
						glBegin(GL_QUADS);
						{
							glVertex3d(-3.3, .9, 0);
							glVertex3d( 3.3, .9, 0);
							glVertex3d( 3.3, .9, 7.2);
							glVertex3d(-3.3, .9, 7.2);
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
				// 
				// water 
				//
				//RenderWater();
			}
		}

		inline void DrawTestCube()
		{
				Model* theModel = static_cast<Model*>(model); 

				glEnable(GL_TEXTURE_2D);
				glColor3f(1.0f, 1.0f, 1.0f);
				glPushMatrix();

				Matrix4d m;
				IElement* lake = theModel->Lake(&m); 
				glMultMatrixd(m.data()); 

				glTranslated( 0, 1, 3  );

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






// #define GL_CLAMP_TO_EDGE 0x812F

		GLuint reflection;

		int texSize; 

		GLuint rboId;

		inline void InitReflectionFBO() 
		{
			int TEXTURE_WIDTH = texSize;
			int TEXTURE_HEIGHT = texSize;
			//
			// create a texture object
			GLuint& textureId = reflection;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0,
						 GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glBindTexture(GL_TEXTURE_2D, 0);

			// create a renderbuffer object to store depth info
			glGenRenderbuffers(1, &rboId);
			glBindRenderbuffer(GL_RENDERBUFFER, rboId);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
								  TEXTURE_WIDTH, TEXTURE_HEIGHT);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			// create a framebuffer object
			GLuint fboId;
			glGenFramebuffers(1, &fboId);
			glBindFramebuffer(GL_FRAMEBUFFER, fboId);

			// attach the texture to FBO color attachment point
			glFramebufferTexture2D(GL_FRAMEBUFFER,        // 1. fbo target: GL_FRAMEBUFFER 
								   GL_COLOR_ATTACHMENT0,  // 2. attachment point
								   GL_TEXTURE_2D,         // 3. tex target: GL_TEXTURE_2D
								   textureId,             // 4. tex ID
								   0);                    // 5. mipmap level: 0(base)

			// attach the renderbuffer to depth attachment point
			glFramebufferRenderbuffer(GL_FRAMEBUFFER,      // 1. fbo target: GL_FRAMEBUFFER
									  GL_DEPTH_ATTACHMENT, // 2. attachment point
									  GL_RENDERBUFFER,     // 3. rbo target: GL_RENDERBUFFER
									  rboId);              // 4. rbo ID

			// check FBO status
			//GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			//if(status != GL_FRAMEBUFFER_COMPLETE)
			//	fboUsed = false;

			// switch back to window-system-provided framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}


		inline void RenderReflection()
		{
			glViewport(0,0, texSize, texSize);
			//
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//
			SetUpCamera();
			//
			Lights();
			//
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.0f);
				glScalef(1.0, -1.0, 1.0);
				double plane[4] = {0.0, 1.0, 0.0, 0.0}; //water at y=0
				glEnable(GL_CLIP_PLANE0);
				glClipPlane(GL_CLIP_PLANE0, plane);
				//
				DrawingContext ctx1;
				ctx1.skipMirrors = true;
				model->Draw(ctx1);   
				//
				glDisable(GL_CLIP_PLANE0);
			}
			glPopMatrix();

			//render reflection to texture
			glBindTexture(GL_TEXTURE_2D, reflection);
			//glCopyTexSubImage2D copies the frame buffer
			//to the bound texture
			glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0,texSize, texSize);
		}

		//inline void RenderWater() 
		//{
		//	//bind & enable shader programs
		//	glEnable(GL_VERTEX_PROGRAM_ARB);
		//	glEnable(GL_FRAGMENT_PROGRAM_ARB);
		//	glBindProgramARB(GL_VERTEX_PROGRAM_ARB, myVertexProgram);
		//	glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, myFragmentProgram);

		//	//move texture across water surface
		//	glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB, 0, texmove,texmove,texmove, 1.0f);
		//	glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB, 1, -texmove,-texmove,-texmove, 1.0f);
		//	//Set viewposition and lightposition
		//	glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB, 2, viewpos.x,viewpos.y,viewpos.z, 1.0f);
		//	glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB, 3, lightpos.x,lightpos.y,lightpos.z, 1.0f);

		//	//Set watercolor
		//	glProgramLocalParameter4fARB(GL_FRAGMENT_PROGRAM_ARB, 0, water.red,water.green,water.blue, 1.0f);

		//	//bind all textures
		//	glActiveTextureARB(GL_TEXTURE0_ARB);
		//	glEnable(GL_TEXTURE_2D);
		//	glBindTexture(GL_TEXTURE_2D, reflection);

		//	glActiveTextureARB(GL_TEXTURE1_ARB);
		//	glEnable(GL_TEXTURE_2D);
		//	glBindTexture(GL_TEXTURE_2D, refraction);

		//	glActiveTextureARB(GL_TEXTURE2_ARB);
		//	glEnable(GL_TEXTURE_2D);
		//	glBindTexture(GL_TEXTURE_2D, normalmap);

		//	glActiveTextureARB(GL_TEXTURE3_ARB);
		//	glEnable(GL_TEXTURE_2D);
		//	glBindTexture(GL_TEXTURE_2D, dudvmap);

		//	glActiveTextureARB(GL_TEXTURE4_ARB);
		//	glEnable(GL_TEXTURE_2D);
		//	glBindTexture(GL_TEXTURE_2D, depth);

		//	//Render the water surface
		//	glBegin(GL_QUADS);
		//	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 5.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0.0f, 1.0f);
		//	glVertex3f(-5.0f, 0.0f, 5.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 0.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0.0f, 1.0f);
		//	glVertex3f(-5.0f, 0.0f, -5.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 5.0f, 0.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0.0f, 1.0f);
		//	glVertex3f(5.0f, 0.0f, -5.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 5.0f, 5.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0.0f, 1.0f);
		//	glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0.0f, 1.0f);
		//	glVertex3f(5.0f, 0.0f, 5.0f);
		//	glEnd();
		//}









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
					Matrix4d R = Matrix4d::Identity();
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
					Matrix4d R = Matrix4d::Identity();
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
			switch(key) 
			{
			case 27:        // When Escape Is Pressed...
				{
					exit ( 0 );   // Exit The Program
				}
				break;     
			case 'f':
				{
					fp=TRUE;
					filter+=1;
					if (filter>2)
					{
						filter=0;
					}
				}
				break;
			case '=':
			case '+':
				{
					cameraLocation = Math::ScaleMatrix(1.0 / 1.2) * cameraLocation; 
					glutPostRedisplay();
				}
				break;
			case '_':
			case '-':
				{
					cameraLocation = Math::ScaleMatrix(1.2) * cameraLocation; 
					glutPostRedisplay();
				}
				break;
			case 'l':
				{
					lp=TRUE;
					enableLighting=!enableLighting;
					//
					if (!enableLighting)
					{
						glDisable(GL_LIGHTING);
					}
					else
					{
						glEnable(GL_LIGHTING);
					}
					glutPostRedisplay();
				}
				break;
			case 'b':
				{
					bp=TRUE;
					blend = !blend;
					//
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
				}
				break;
			case 'r':
				{
					yspeed+=0.01f;
				}
				break;
			//
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




		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Dynamics 

		void OnIdle()
		{
			model->Act(10); 
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

