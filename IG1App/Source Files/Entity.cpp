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
 // _____   ____  _      ___________  ____  _   _  ____
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
//-------------------------------------------------------------------------

Sierpinski::Sierpinski(GLdouble rd, GLuint numP)
{
	mMesh = Mesh::generaSierpinski(rd, numP);
}

Sierpinski::~Sierpinski()
{
	delete mMesh; mMesh = nullptr;
}

void Sierpinski::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glPointSize(2);
		mMesh->render();
		glPointSize(1);
		glColor3d(1.0, 1.0, 1.0);
	}
}
//-------------------------------------------------------------------------

TrianguloRGB::TrianguloRGB(GLdouble rd)
{
	mMesh = Mesh::generaTrianguloRGB(rd);

}

TrianguloRGB::~TrianguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void TrianguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_BACK, GL_LINE);

		mMesh->render();
		glColor3d(1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	}
}
//-------------------------------------------------------------------------

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectanguloRGB(w,h);
}

RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_BACK, GL_LINE);


		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
//-------------------------------------------------------------------------
