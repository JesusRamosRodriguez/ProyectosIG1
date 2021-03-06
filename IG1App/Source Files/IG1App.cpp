#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------

void IG1App::close()
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//P0. 9. ANIMACI�N OPCIONAL 
void IG1App::update()
{
	if (anim_) {
		if (glutGet(GLUT_ELAPSED_TIME) - mLastUpdateTime > 17)
		{
			mScene->update();
			mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
			glutPostRedisplay();
		}
	}
	//la diferencia entre el tiempo actual y el recogido en la variable = al tiempo que pas�
	//la variable recoge el tiempo y luego se opera 
}

void IG1App::setBoolAnimation()
{
	anim_ = !anim_;
}

//*******P1.1
void IG1App::mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		mMouseButt = button;
		mMouseCoord = glm::dvec2(x, mWinH - y);
	}
}
void IG1App::motion(int x, int y)
{
	//panear
	if (mMouseButt == GLUT_RIGHT_BUTTON) {
		glm::dvec2 mp = mMouseCoord;
		mMouseCoord = glm::dvec2(x, mWinH - y);
		mp -= mMouseCoord;
		
		mCamera->moveLR(mp.x);
		mCamera->moveUD(mp.y);

		glutPostRedisplay();
	}
	//orbitar 
	else if (mMouseButt == GLUT_LEFT_BUTTON) {
		glm::dvec2 mp = mMouseCoord;
		mMouseCoord = glm::dvec2(x, mWinH - y);
		mp -= mMouseCoord;
		
		mCamera->orbit((mp.x * 0.05), mp.y); // sensitivity = 0.05 //����HAY QUE DEFINIRLO EN LA CLASE CAMERA
		glutPostRedisplay();
	}
	
}
//-------------------------------------------------------------------------



void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mScene = new Scene;


	anim_ = false;
	mLastUpdateTime = 0;

	mCamera->set2D();
	mScene->init();
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL()
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   

	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutIdleFunc(s_update);

	//*******P1.2
	glutMouseFunc(s_mouse); //cuando se presiona o suelta un bot�n
	glutMotionFunc(s_motion); //cuando se mueve con un bot�n presionado
	//glutMouseWheelFunc(s_mouseWheel); // cuando se gira una rueda

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free()
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mViewPort; mViewPort = nullptr;
}
//-------------------------------------------------------------------------

void IG1App::display() const
{  // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	mScene->render(*mCamera);  // uploads the viewport and camera to the GPU

	glutSwapBuffers();	// swaps the front and back buffer
}
//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		mCamera->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D();
		break;
	case 'u':
		//mScene->update();
		setBoolAnimation();
		break;
	case '0':
		mScene->setState(0);
		break;
	case '1':
		mScene->setState(1);
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
	case GLUT_KEY_RIGHT:
		mCamera->moveLR(7.0);
		break;
	case GLUT_KEY_LEFT:
		mCamera->moveLR(-7.0);
		break;
	case GLUT_KEY_UP:
		mCamera->moveUD(7.0);
		break;
	case GLUT_KEY_DOWN:
		mCamera->moveUD(-7.0);
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

