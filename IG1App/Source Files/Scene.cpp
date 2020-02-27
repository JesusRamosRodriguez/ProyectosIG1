#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{
	//****************
	setGL();  // OpenGL settings

	//open state
	if (mId_ == 0)
		scene2D();
	else if (mId_ == 1)
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

		//eliminamos texturas y limpiamos vector
	for (Texture* t : gTextures)
	{
		delete t;  t = nullptr;
	}
	gTextures.clear();

	//eliminamos objetos y limpiamos vector
	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();

}
//-------------------------------------------------------------------------
void Scene::setGL()
{
	// OpenGL basic setting
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);
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
void Scene::setState(int id)
{
	if (mId_ != id) {
		mId_ = id;
		//clean all scene
		free();
		resetGL();
		init();
	}
}

//-------------------------------------------------------------------------
void Scene::scene2D()
{
	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	Poligono* triangulo_ = new Poligono(3.0, 100.0);				//1. Polígono regular (Dibujo de líneas) 
	Poligono* circunferencia_ = new Poligono(360.0, 300.0);			//1. Polígono regular (Dibujo de líneas)
	Sierpinski* sierpinski_ = new Sierpinski(300.0, 100000.0);			//2. Triangulo de Sierpinski
	TrianguloRGB* trianguloRGB_ = new TrianguloRGB(50.0);				//3. TriánguloRGB
	RectanguloRGB* rectanguloRGB_ = new RectanguloRGB(800.0, 600.0);	//4-5. RectánguloRGB

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
//-------------------------------------------------------------------------
void Scene::scene3D()
{
	// allocate memory and load resources
	// Lights


	// Graphics objects (entities) of the scene
	//----		Elementos de la escena SIN Textura	----
	EstrellaConTextura* estrella3D_ = new EstrellaConTextura(80.0, 6.0, 100.0);	//6. Estrella 3D

	GLdouble estrH_ = 200.0;  estrella3D_->setH(estrH_);//será la altura de la estrella, se actualiza en su update para la animacion
	//Caja* caja_ = newCaja(200.0);

	// ----		Elementos de la escena CON Textura	 ----
	CajaConTextura* cajaT_ = new CajaConTextura(200.0);
	Suelo* suelo_ = new Suelo(700, 450.0, 5, 5); //11. Suelo con textura
	Suelo* caja_fondo_ = new Suelo(200.0, 200.0, 1, 1);		 //13 fondo de la caja: parte opcional
	Foto* foto_ = new Foto(200.0, 150.0, 1, 1); //15. foto con renderizado del buffer como textura


	//Colores
	//(..........)



	// Textures ***	0: triangulo --- 1: caja (exterior), 2: caja (interior) --- 3: suelo adoquinado; 
	gTextures.push_back(new Texture()); //0
	gTextures[0]->load("../Bmps/baldosaP.bmp"); //0
	gTextures.push_back(new Texture()); //1
	gTextures[1]->load("../Bmps/container.bmp"); //1
	gTextures.push_back(new Texture());//2
	gTextures[2]->load("../Bmps/papelE.bmp"); //2
	gTextures.push_back(new Texture());//3
	gTextures[3]->load("../Bmps/baldosaC.bmp"); //3


	//modificamos el atributo del objeto
	estrella3D_->setTexure(gTextures[0]);
	cajaT_->setTexure(gTextures[1]);
	cajaT_->setIntTex(gTextures[2]);
	suelo_->setTexure(gTextures[3]);
	caja_fondo_->setTexure(gTextures[1]);
	foto_->setTexure(gTextures[0]);

	//Transforms
	estrella3D_->setModelMat(translate(estrella3D_->modelMat(), dvec3(0.0, estrH_, 0.0)));
	suelo_->setModelMat(translate(suelo_->modelMat(), dvec3(0.0, 0.0, -100.0)));
	caja_fondo_->setModelMat(translate(caja_fondo_->modelMat(), dvec3(0.0, 0.0, -98)));
	foto_->setModelMat(translate(foto_->modelMat(), dvec3(200, 0.0, -98)));


	//Entities
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(estrella3D_);
	gObjects.push_back(cajaT_);
	gObjects.push_back(suelo_);
	gObjects.push_back(caja_fondo_);
	gObjects.push_back(foto_);
}
//-------------------------------------------------------------------------