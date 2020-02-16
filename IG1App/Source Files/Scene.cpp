#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	//*****************************
   
				//SCENES
	// allocate memory and load resources
	// Lights
	// Textures

	//scene2D(); //Enunciado P0. EJERCICIOS P1: [1-6)
	scene3D();

	

}
//-------------------------------------------------------------------------

void Scene::update()
{
	for (auto it = gObjects.begin(); it < gObjects.end(); it++)
	{
		if (*it != nullptr)
			(*it)->update();
	}
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
void Scene::scene2D()
{
	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	Poligono* triangulo_ = new Poligono(3.0, 100.0);				//1. Pol�gono regular (Dibujo de l�neas) 
	Poligono* circunferencia_ = new Poligono(360.0, 300.0);			//1. Pol�gono regular (Dibujo de l�neas)
	Sierpinski* sierpinski_ = new Sierpinski(300, 100000);			//2. Triangulo de Sierpinski
	TrianguloRGB* trianguloRGB_ = new TrianguloRGB(50);				//3. Tri�nguloRGB
	RectanguloRGB* rectanguloRGB_ = new RectanguloRGB(800, 600);	//4-5. Rect�nguloRGB

	//Colores
	sierpinski_->setColor(glm::dvec4(1.0, 1.0, 0.0, 1.0));
	triangulo_->setColor(glm::dvec4(1.0, 1.0, 0.0, 1.0));
	circunferencia_->setColor(glm::dvec4(1.0, 0.0, 1.0, 1.0));

	//Transforms
	rectanguloRGB_->setModelMat(translate(rectanguloRGB_->modelMat(), dvec3(0.0, 0.0, -100.0)));
	//Entities
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(sierpinski_);
	gObjects.push_back(triangulo_);
	gObjects.push_back(circunferencia_);
	gObjects.push_back(trianguloRGB_);
	gObjects.push_back(rectanguloRGB_);

}
void Scene::scene3D()
{
	// Graphics objects (entities) of the scene
	Estrella3D* estrella3D_ = new Estrella3D(250, 6, 100);	//6. Estrella 3D


	//Colores


	//Transforms

	//Entities
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(estrella3D_);
}
//-------------------------------------------------------------------------