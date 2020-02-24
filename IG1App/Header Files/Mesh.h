//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include <vector>

//-------------------------------------------------------------------------

class Mesh 
{
public:

	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh

	static Mesh* generaPoligono(GLuint numL, GLdouble rd);		//1 Polígono regular (Dibujo de líneas)
	static Mesh* generaSierpinski(GLdouble rd, GLuint numP);	//2. Triangulo de Sierpinski
	static Mesh* generaTrianguloRGB(GLdouble rd);				//3. TriánguloRGB
	static Mesh* generaRectangulo(GLdouble w, GLdouble h);		//4. Rectángulo
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);	//5. RectánguloRGB
	static Mesh* generaEstrella3D(GLdouble re, GLdouble np, GLdouble h); //6. Estrella 3D 9.renderizado doble
	static Mesh* generaContCubo(GLdouble ld);	//7. Caja

	//P1 TEXTURAS
	static Mesh* generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h); //10.
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);//11.suelo con textura
	static Mesh* generaCuboTexCor(GLdouble nl); //14. caja con textura


	Mesh() {};
	virtual ~Mesh() {};

	Mesh(const Mesh & m) = delete;  // no copy constructor
	Mesh & operator=(const Mesh & m) = delete;  // no copy assignment
			
	virtual void render() const;
	
	GLuint size() const { return mNumVertices; };   // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };
		
protected:
	
	GLuint mPrimitive = GL_TRIANGLES;   // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0;  // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices;  // vertex array
	std::vector<glm::dvec4> vColors;    // color array
	virtual void draw() const;

	std::vector<glm::dvec2> vTexCoords; //P1. texturas
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_