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

void Abs_Entity::setColor(glm::dvec4 c) { mColor = c; }

void Abs_Entity::setTexure(Texture* t)
{
	mTexture = t;
}

		//*****************************//



//-------------------------------------------------------------------------

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
	angTr_ = 0.0;
	angRt_ = 0.0;
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

void TrianguloRGB::update()
{
	mModelMat = translate(dmat4(1), dvec3(300.0 * cos(radians(angTr_)), 300.0 * sin(radians(angTr_)), 0));
	mModelMat = rotate(mModelMat, radians(angRt_), dvec3(0, 0, 1));
	angTr_ -= 1;
	angRt_ += 1;
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

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	mMesh = Mesh::generaEstrella3D(re, np, h);
	grdY_ = grdZ_ = 0.0;
}

Estrella3D::~Estrella3D()
{
	delete mMesh; mMesh = nullptr;
}

void Estrella3D::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//mTexture->bind(GL_REPLACE); //en la clase texture tenemos indicaciones en los metodos propios

		mMesh->render();

		//rotacion de la estrella sobre su eje
		aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));
		upload(aMat);

		mMesh->render();

		mTexture->unbind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glColor3d(1.0, 1.0, 1.0);
	}
}
void Estrella3D::update()
{
	//siempre se empieza la transformacion desde la matriz identidad, que es donde se aplica la operacion
	mModelMat = translate(dmat4(1), dvec3(0, 250, 0));
	//una vez actualizado mModelMat no hace falta más pasar por parametro la matriz identidad
	mModelMat = rotate(mModelMat, radians(grdY_), dvec3(0, 1, 0));
	mModelMat = rotate(mModelMat, radians(grdZ_), dvec3(0, 0, 1));
	grdY_ += 1;
	grdZ_ += 1;
}
//-------------------------------------------------------------------------

Caja::Caja(GLdouble ld)
{
	mMesh = Mesh::generaContCubo(ld);
}

Caja::~Caja()
{
	delete mMesh; mMesh = nullptr;
}

void Caja::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//mTexture->bind(GL_REPLACE);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glColor3d(1.0, 1.0, 1.0);
	}
}

//-------------------------------------------------------------------------
Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	//establecer la matriz de modelado en plano horizontal
	mModelMat = rotate(dmat4(1), radians(-90.0), dvec3(1, 0, 0));
	
}

Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
	delete mTexture; mTexture = nullptr;
}

void Suelo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->bind(GL_REPLACE);

		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}
