#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
#include <iostream> // TEMP!
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------

 /*                                 _____      _ _
								 |  __ \    | (_)
   __ _  ___ _ __   ___ _ __ __ _| |__) |__ | |_  __ _  ___  _ __   ___  ___
  / _` |/ _ \ '_ \ / _ \ '__/ _` |  ___/ _ \| | |/ _` |/ _ \| '_ \ / _ \/ __|
 | (_| |  __/ | | |  __/ | | (_| | |  | (_) | | | (_| | (_) | | | | (_) \__ \
  \__, |\___|_| |_|\___|_|  \__,_|_|   \___/|_|_|\__, |\___/|_| |_|\___/|___/
   __/ |                                          __/ |
  |___/                                          |___/                       */

Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = numL;
	mesh->vVertices.reserve(mesh->mNumVertices);

	double x = 0.0, y = 0.0;
	double grados = 90.0;
	
	//Para generar los vértices utiliza la ecuación de la circunferencia con centro C y radio R :
	for (int i = 0; i < numL; i++) {
		//se ajusta la posición de los vertices transformados a radianes
		x = rd * cos(radians(grados));
		y = rd * sin(radians(grados));
		//se establecen las coord.
		mesh->vVertices.emplace_back(x, y, 0.0);
		//se incrementa el ángulo en base a la nueva posición
		grados += 360.0 / numL;
	}

	return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_POINTS;

    mesh->mNumVertices = numP;
    mesh->vVertices.reserve(mesh->mNumVertices);

    double x = 0.0, y = 0.0;
    double grados = 90.0;

        //main Triangulo
    Mesh* mainTriangulo = generaPoligono(3, rd);
    for (size_t i = 0; i < 3; i++)
    {
        mesh->vVertices.emplace_back(mainTriangulo->vVertices[i]);
    }
    
    int randomP = 0;
    dvec3 Tk = mesh->vVertices[rand() % 3];
    dvec3 newP = dvec3(0);
    dvec3 prevP = dvec3(0);

    for (size_t i = 3; i < numP; i++)
    {
        prevP = mesh->vVertices[i - 1];
        newP = dvec3((prevP.x + Tk.x)/2, (prevP.y + Tk.y)/2, 0.0);

        mesh->vVertices.emplace_back(newP.x, newP.y, 0.0);
     
        Tk = mesh->vVertices[rand() % 3];
    }

    delete mainTriangulo; mainTriangulo = nullptr;

    return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaTrianguloRGB(GLdouble rd)
{
 
   Mesh* mesh = generaPoligono(3, rd);
   mesh->mPrimitive = GL_TRIANGLES;

   mesh->vColors.reserve(3);
   mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
   mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
   mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

   return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    //Valores comunes
    int x = w / 2, y = h / 2, z = 0;

    //4 vertices en orden
    mesh->vVertices.emplace_back(-x, y, z);
    mesh->vVertices.emplace_back(-x, -y, z);
    mesh->vVertices.emplace_back(x, y, z);
    mesh->vVertices.emplace_back(x, -y, z);

       
    return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
    Mesh* mesh = generaRectangulo(w, h);

    mesh->vColors.reserve(4);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

    return mesh;
}
//-------------------------------------------------------------------------