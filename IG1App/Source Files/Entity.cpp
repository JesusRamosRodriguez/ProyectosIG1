#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------
 //				  | |          | |                             
 // _ __ ___   ___| |_ ___   __| | ___  ___    __ _ _   ___  __
 //| '_ ` _ \ / _ \ __/ _ \ / _` |/ _ \/ __|  / _` | | | \ \/ /
 //| | | | | |  __/ || (_) | (_| | (_) \__ \ | (_| | |_| |>  < 
 //|_| |_| |_|\___|\__\___/ \__,_|\___/|___/  \__,_|\__,_/_/\_\

void Abs_Entity::setColor(glm::dvec4 c) { mColor = c; }

		//*****************************//



//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

 //|  __ \ / __ \| |    |_   _/ ____|/ __ \| \ | |/ __ \ 
 //| |__) | |  | | |      | || |  __| |  | |  \| | |  | |
 //|  ___/| |  | | |      | || | |_ | |  | | . ` | |  | |
 //| |    | |__| | |____ _| || |__| | |__| | |\  | |__| |
 //|_|     \____/|______|_____\_____|\____/|_| \_|\____/

Poligono::Poligono(GLdouble numL, GLdouble rd)
{
	mMesh = Mesh::generaPoligono(numL, rd);
}

Poligono::~Poligono()
{
	delete mMesh; mMesh = nullptr;
}

void Poligono::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		glColor3d(1.0, 1.0, 1.0);
	}
}
