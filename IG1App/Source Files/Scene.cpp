#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	// allocate memory and load resources
    // Lights
    // Textures

    // Graphics objects (entities) of the scene
	Sierpinski* sierpinski_ = new Sierpinski(300, 100000);
	Poligono* triangulo_ = new Poligono(3.0, 100.0);		//1. Polígono regular (Dibujo de líneas) 
	Poligono* circunferencia_ = new Poligono(360.0, 100.0);	//1. Polígono regular (Dibujo de líneas)
	TrianguloRGB* trianguloRGB_ = new TrianguloRGB(200);
	//Colores
	sierpinski_->setColor(glm::dvec4(1.0, 1.0, 0.0, 1.0));
	triangulo_->setColor(glm::dvec4(1.0, 1.0, 0.0, 1.0));
	circunferencia_->setColor(glm::dvec4(0.8, 0.2, 0.4, 1.0));


	gObjects.push_back(new EjesRGB(400.0));

	//Entities
	gObjects.push_back(sierpinski_);
	gObjects.push_back(triangulo_);
	gObjects.push_back(circunferencia_);
	gObjects.push_back(trianguloRGB_);


	
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------


