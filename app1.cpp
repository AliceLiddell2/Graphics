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
  switch ( a_keys ) {
    case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
      xspeed-=0.01f;
      break;
    case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
      xspeed+=0.01f;
      break;
    case GLUT_KEY_RIGHT:
    	yspeed+=0.01f;
      break;
    case GLUT_KEY_LEFT:
    	yspeed-=0.01f;
    	break;
    case GLUT_KEY_F1:
    	glutFullScreen ();
      break;
    case GLUT_KEY_F2:
    	glutReshapeWindow ( 500, 500 );
      break;
    default:
      break;
  }
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
  glutInitWindowPosition (0,0);

  int initialW = 720;
  int initialH = 540;
  glutInitWindowSize  ( initialW, initialH ); // If glutFullScreen wasn't called this is the window size
  Scene3D& scene = Scene3D::MainScene();
  // scene.SetViewPort(initialW, initialH);

  glutCreateWindow    ( "Lab" ); // Window Title (argv[0] for current directory as title)

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



