#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
//#include <gtc/matrix_access.hpp>

using namespace glm;

//-------------------------------------------------------------------------

Camera::Camera(Viewport* vp): mViewPort(vp), mViewMat(1.0), mProjMat(1.0),  
							  xRight(vp->width() / 2.0), xLeft(-xRight),
							  yTop(vp->height() / 2.0), yBot(-yTop), mRad(1000), mAng(0.0)
{
    setPM();
}
//-------------------------------------------------------------------------

void Camera::uploadVM() const 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(mViewMat)); // transfers view matrix to the GPU 
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
	mViewMat = lookAt(mEye, mLook, mUp);  // glm::lookAt defines the view matrix 
	//P1.2
	//implementamos el m�todo setAxes
	setAxes();
}
//-------------------------------------------------------------------------

void Camera::set2D() 
{
	mEye = dvec3(0, 0, 500);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 1, 0);
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
	mEye = dvec3(500, 500, 500);  
	mLook = dvec3(0, 10, 0);   
	mUp = dvec3(0, 1, 0);
	setVM();
}
//-------------------------------------------------------------------------

//SE COMENTAN POR INDICACI�N DEL ENUNCIADO DE LA PRACTICA
//void Camera::pitch(GLdouble a) 
//{  
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
////-------------------------------------------------------------------------
//
//void Camera::yaw(GLdouble a) 
//{
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
////-------------------------------------------------------------------------
//
//void Camera::roll(GLdouble a) 
//{
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble xw, GLdouble yh) 
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setScale(GLdouble s) 
{
	mScaleFact -= s;
	if (mScaleFact < 0) mScaleFact = 0.01;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft*mScaleFact, xRight*mScaleFact, yBot*mScaleFact, yTop*mScaleFact, mNearVal, mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
}

//-------------------------------------------------------------------------

void Camera::uploadPM() const 
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(mProjMat)); // transfers projection matrix to the GPU
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------
 // _____  _____            _____ _______ _____ _____            __   ___  
 //|  __ \|  __ \     /\   / ____|__   __|_   _/ ____|   /\     /_ | |__ \ 
 //| |__) | |__) |   /  \ | |       | |    | || |       /  \     | |    ) |
 //|  ___/|  _  /   / /\ \| |       | |    | || |      / /\ \    | |   / / 
 //| |    | | \ \  / ____ \ |____   | |   _| || |____ / ____ \   | |_ / /_ 
 //|_|    |_|  \_\/_/    \_\_____|  |_|  |_____\_____/_/    \_\  |_(_)____
void Camera::moveLR(GLdouble cs)
{
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();
}
void Camera::moveFB(GLdouble cs)
{
	mEye += mFront * cs;
	mLook += mFront * cs;
	setVM();
}
void Camera::moveUD(GLdouble cs)
{
	mEye += mUpward * cs;
	mLook += mUpward * cs; 
	setVM();
}
void Camera::orbit(GLdouble incAng, GLdouble incY)
{
	mAng += incAng;
	mEye.x = mLook.x + cos(radians(mAng)) * mRad;
	mEye.z = mLook.z - sin(radians(mAng)) * mRad;
	mEye.y += incY;
	setVM();
}


//SE INCLUYE EN EL M�TODO setVM
void Camera::setAxes()
{
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}
//-------------------------------------------------------------------------
