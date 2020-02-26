//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity() : mModelMat(1.0), mColor(1), mTexture(nullptr) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	virtual void update() {};

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	//aux methods
	void setColor(glm::dvec4 c);
	void setTexure(Texture* t);

protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix

	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const;

	//ATRIBUTOS AUXILIARES
	glm::dvec4 mColor;

	//texturas
	Texture* mTexture; //se elimina en la clase Scene.free() [vector punteros a texturas] No eliminar en las destructuras de entity
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Poligono : public Abs_Entity
{
public:
	explicit Poligono(GLdouble numL, GLdouble rd);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------

class Sierpinski : public Abs_Entity
{
public:
	explicit Sierpinski(GLdouble rd, GLuint numP);
	~Sierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------

class TrianguloRGB : public Abs_Entity
{
public:
	explicit TrianguloRGB(GLdouble rd);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
protected:
	GLdouble angTr_, angRt_;
};
//-------------------------------------------------------------------------

class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------

class Estrella3D : public Abs_Entity
{
public:
	explicit Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();

	void setH(GLdouble h);

private:
	GLdouble grdY_, grdZ_;
	GLdouble h_;
};
//-------------------------------------------------------------------------
class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble ld);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
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

class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------
class CajaConTextura : public Abs_Entity
{
public:
	explicit CajaConTextura(GLdouble ld);
	~CajaConTextura();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	//metodo modifica la textura interior
	void setIntTex(Texture* t);

private:
	//segunda textura: interior caja
	Texture* iTexture_;
};
//-------------------------------------------------------------------------
class EstrellaConTextura : public Abs_Entity
{
public:
	explicit EstrellaConTextura(GLdouble re, GLdouble np, GLdouble h);
	~EstrellaConTextura();

	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();

	void setH(GLdouble h);

private:
	GLdouble grdY_, grdZ_;
	GLdouble h_;
};

//-------------------------------------------------------------------------
class Foto : public Abs_Entity
{
public:
	explicit Foto(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

#endif //_H_Entities_H_