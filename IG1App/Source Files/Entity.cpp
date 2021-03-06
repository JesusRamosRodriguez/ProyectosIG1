#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "IG1App.h"

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l) : Abs_Entity()
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
	mMesh = Mesh::generaRectanguloRGB(w, h);
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

		mMesh->render();

		//rotacion de la estrella sobre su eje
		aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));
		upload(aMat);

		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glColor3d(1.0, 1.0, 1.0);
	}
}
void Estrella3D::update()
{
	//siempre se empieza la transformacion desde la matriz identidad, que es donde se aplica la operacion
	mModelMat = translate(dmat4(1), dvec3(0, h_, 0));
	//una vez actualizado mModelMat no hace falta m�s pasar por parametro la matriz identidad
	mModelMat = rotate(mModelMat, radians(grdY_), dvec3(0, 1, 0));
	mModelMat = rotate(mModelMat, radians(grdZ_), dvec3(0, 0, 1));
	grdY_ += 1;
	grdZ_ += 1;
}
void Estrella3D::setH(GLdouble h)
{
	h_ = h;
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
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glColor3d(1.0, 1.0, 1.0);
	}
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
/* _______ ________   _________ _    _ _____             _____
 |__   __|  ____\ \ / /__   __| |  | |  __ \     /\    / ____|
	| |  | |__   \ V /   | |  | |  | | |__) |   /  \  | (___
	| |  |  __|   > <    | |  | |  | |  _  /   / /\ \  \___ \
	| |  | |____ / . \   | |  | |__| | | \ \  / ____ \ ____) |
	|_|  |______/_/ \_\  |_|   \____/|_|  \_\/_/    \_\_____/*/
	//-------------------------------------------------------------------------
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
}

void Suelo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mTexture->bind(GL_REPLACE);

		mMesh->render();

		mTexture->unbind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

//-------------------------------------------------------------------------
CajaConTextura::CajaConTextura(GLdouble ld)
{
	mMesh = Mesh::generaCuboTexCor(ld);
	iTexture_ = nullptr;
}

CajaConTextura::~CajaConTextura()
{
	delete mMesh;  mMesh = nullptr;
}

void CajaConTextura::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mTexture->bind(GL_REPLACE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		mMesh->render();

		mTexture->unbind();


		iTexture_->bind(GL_REPLACE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		mMesh->render();

		iTexture_->unbind();

		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

}

void CajaConTextura::setIntTex(Texture* t)
{
	iTexture_ = t;
}
//-------------------------------------------------------------------------

EstrellaConTextura::EstrellaConTextura(GLdouble re, GLdouble np, GLdouble h)
{
	mMesh = Mesh::generaEstrellaTexCor(re, np, h);
	grdY_ = grdZ_ = 0.0;
	x_ = y_ = z_ = 0.0;
}

EstrellaConTextura::~EstrellaConTextura()
{
	delete mMesh; mMesh = nullptr;
}

void EstrellaConTextura::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mTexture->bind(GL_REPLACE);

		mMesh->render();

		//rotacion de la estrella sobre su eje
		aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));
		upload(aMat);

		mMesh->render();

		mTexture->unbind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void EstrellaConTextura::update()
{
	//siempre se empieza la transformacion desde la matriz identidad, que es donde se aplica la operacion
	mModelMat = translate(dmat4(1), dvec3(x_, y_, z_));
	//una vez actualizado mModelMat no hace falta m�s pasar por parametro la matriz identidad
	mModelMat = rotate(mModelMat, radians(grdY_), dvec3(0, 1, 0));
	mModelMat = rotate(mModelMat, radians(grdZ_), dvec3(0, 0, 1));
	grdY_ += 1;
	grdZ_ += 1;
}

void EstrellaConTextura::setY(GLdouble h){y_ = h;}
void EstrellaConTextura::setX(GLdouble x){x_ = x;}
void EstrellaConTextura::setZ(GLdouble z){z_ = z;}
//-------------------------------------------------------------------------

Foto::Foto(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);

	//establecer la matriz de modelado en plano horizontal
	mModelMat = rotate(dmat4(1), radians(-90.0), dvec3(1, 0, 0));
}

Foto::~Foto()
{
	delete mMesh; mMesh = nullptr;
}

void Foto::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		mTexture->bind(GL_REPLACE);

		mMesh->render();

		mTexture->unbind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Foto::update()
{
	mTexture->loadColorBuffer(IG1App::s_ig1app.getWinWidth(), IG1App::s_ig1app.getWinHeight());
}



//-------------------------------------------------------------------------
Cristalera::Cristalera(GLdouble ld)
{
	mMesh = Mesh::generaCuboTexCor(ld);
}

Cristalera::~Cristalera()
{
	delete mMesh; mMesh = nullptr;
}

void Cristalera::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		
		mTexture->bind(GL_REPLACE);

		glDisable(GL_ALPHA_TEST);
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mMesh->render();

		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		glEnable(GL_ALPHA_TEST);
		mTexture->unbind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}
}

Planta::Planta(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);

	//establecer la matriz de modelado en plano horizontal
	mModelMat = rotate(dmat4(1), radians(-90.0), dvec3(1, 0, 0));
}

Planta::~Planta()
{
	delete mMesh; mMesh = nullptr;
}

void Planta::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);


		mTexture->bind(GL_REPLACE);
	
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mMesh->render();

		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		mTexture->unbind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
