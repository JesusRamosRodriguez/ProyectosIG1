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

    //vector coord de textura
    if (vTexCoords.size() > 0) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
    }
   
	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

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

Mesh* Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h)
{
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_FAN;
    mesh->mNumVertices = 2 * np + 2;
    mesh->vVertices.reserve(mesh->mNumVertices);

    GLdouble x = 0.0, y = 0.0, xi = 0.0, yi = 0.0;
    GLdouble grados = 0.0 , incremento = 360 / (mesh->mNumVertices - 2);

    mesh->vVertices.emplace_back(0.0, 0.0, 0.0); //abre con vO
    for (size_t i = 1; i <= np; i++)
    {       
		//radio exterior
        x = re * cos(radians(grados));
        y = re * sin(radians(grados));
        mesh->vVertices.emplace_back(x, y, h);
        grados += incremento;

		//radio interior
        xi = re/2 * cos(radians(grados));
        yi = re/2 * sin(radians(grados));
        mesh->vVertices.emplace_back(xi, yi, h);
        grados += incremento;
    }
    mesh->vVertices.emplace_back(mesh->vVertices[1]); //cierra con V1

    return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaContCubo(GLdouble ld)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	
	mesh->mNumVertices = 10; //8 del cubo + 2 para cerrar el contorno(v0,v1)
	mesh->vVertices.reserve(mesh->mNumVertices);
	
	//posicion vertices en base a ld
	//v0, v1
	mesh->vVertices.emplace_back(-ld / 2, ld/2 , ld / 2);
	mesh->vVertices.emplace_back(-ld / 2, -ld / 2, ld / 2);
	//v2, v3
	mesh->vVertices.emplace_back(ld / 2, ld / 2, ld / 2);
	mesh->vVertices.emplace_back(ld / 2, -ld / 2, ld / 2);
	//v4, v5
	mesh->vVertices.emplace_back(ld / 2, ld / 2, -ld / 2);
	mesh->vVertices.emplace_back(ld / 2, -ld / 2, -ld / 2);
	//v6, v7
	mesh->vVertices.emplace_back(-ld / 2, ld / 2, -ld / 2);
	mesh->vVertices.emplace_back(-ld / 2, -ld / 2, -ld / 2);
	//cerrar contorno
	//v0, v1
	mesh->vVertices.emplace_back(mesh->vVertices[0]);
	mesh->vVertices.emplace_back(mesh->vVertices[1]);

	return mesh;
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

Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = generaEstrella3D(re, np, h);
    mesh->vTexCoords.reserve(mesh->mNumVertices);

    GLdouble x = 0.0, y = 0.0, xi = 0.0, yi = 0.0;
    GLdouble grados = 0.0, incremento = 360 / (mesh->mNumVertices - 2);

    mesh->vTexCoords.emplace_back(0.5, 0.5); //abre con vO
    for (size_t i = 1; i <= np; i++)
    {

        //radio exterior
		x = re * cos(radians(grados));
		y = re * sin(radians(grados));
        mesh->vTexCoords.emplace_back(x, y);
        grados += incremento;

        //radio interior
		xi = re / 2 * cos(radians(grados));
		yi = re / 2 * sin(radians(grados));
        mesh->vTexCoords.emplace_back(xi, yi);

        grados += incremento;
    }
    mesh->vTexCoords.emplace_back(mesh->vTexCoords[1]); //cierra con V1

	return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* mesh = generaRectangulo(w, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);
	mesh->vTexCoords.emplace_back(0,rw);
	mesh->vTexCoords.emplace_back(0,0);
	mesh->vTexCoords.emplace_back(rw,rh);
	mesh->vTexCoords.emplace_back(rh,0);
	return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaCuboTexCor(GLdouble nl)
{
	Mesh* mesh = generaContCubo(nl);
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);
	mesh->vTexCoords.emplace_back(2, 1);
	mesh->vTexCoords.emplace_back(2, 0);
	mesh->vTexCoords.emplace_back(3, 1);
	mesh->vTexCoords.emplace_back(3, 0);

	mesh->vTexCoords.emplace_back(4, 1);
	mesh->vTexCoords.emplace_back(4, 0);

	return mesh;
}

