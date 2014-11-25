// app1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "tgaload.h"

#include "graphics\0.h"

#include "graphics\Model.h"
#include "graphics\Scene.h"

using namespace MyGL;

/*
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
*/

/*
CompoundElement* mainContainer;

Model* model1;
Model* model2;

IScene& Scene3D::mainScene();
*/





void reshape( int w, int h )
{
	if ((!w) || (!h)) return;
	//
	Scene3D& scene = Scene3D::MainScene();
	//
	scene.SetViewPort(w, h);
}

void display(void)
{
	Scene3D::MainScene().Display();
	//*
   xrot+=xspeed;
	yrot+=yspeed;
	//*/

   glutSwapBuffers();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	Scene3D::MainScene().OnKeyPress(key, x, y); 
}

void arrow_keys ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
	Scene3D::MainScene().OnSpecialKey(a_keys, x, y); 
}

void main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
	// ----
	// Model

	Scene3D::MainScene().SetModel(&( Model::GetModel("summer") ));  

	// ----
	// GLUT

  glutInit            ( &argc, argv ); // Erm Just Write It =)
  glutInitDisplayMode ( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA ); // Display Mode

  int initialW = 0, initialH = 0, x0 = 0, y0 = 0;

  if (0 == 1)
  {
	  initialW = 800;
	  initialH = (initialW*3)/4;
  }
  else
  {
		initialW = 480;
		initialH = 320;
		y0 = 480;
  }

  glutInitWindowSize  ( initialW, initialH ); // If glutFullScreen wasn't called this is the window size      
  glutInitWindowPosition ( x0, y0 ); 

  Scene3D& scene = Scene3D::MainScene();
  // scene.SetViewPort(initialW, initialH);

  glutCreateWindow    ( "Lab" );               // Window Title (argv[0] for current directory as title)       

  scene.InitOpenGL();

  //glutFullScreen      ( );          // Put Into Full Screen

  // ----
  // Setting callbacks

  glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
  glutReshapeFunc     ( reshape );
  glutKeyboardFunc    ( keyboard );
  glutSpecialFunc     ( arrow_keys );
  glutIdleFunc		  ( display );
  glutMainLoop        ( );          // Initialize The Main Loop
}



