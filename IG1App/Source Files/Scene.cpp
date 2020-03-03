#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#include "IG1App.h"

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
	//(...)

	// ----		Elementos de la escena CON Textura	 ----
	EstrellaConTextura* estrella3D_ = new EstrellaConTextura(80.0, 6.0, 100.0);	//6. Estrella 3D
	GLdouble estrH_ = 200.0;  estrella3D_->setY(estrH_);//será la altura de la estrella, se actualiza en su update para la animacion
	
	CajaConTextura* cajaT_ = new CajaConTextura(180.0);

	Suelo* suelo_ = new Suelo(900.0, 900.0, 5, 5); //11. Suelo con textura
	Suelo* caja_fondo_ = new Suelo(180.0, 180.0, 1, 1);		 //13 fondo de la caja: parte opcional

	Foto* foto_ = new Foto(200.0, 150.0, 1, 1); //15. foto con renderizado del buffer como textura

	// ----		Elementos de la escena CON BLENDING	 ----
	Cristalera* cristalera_ = new Cristalera(900.0);

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

	gTextures.push_back(new Texture());
	gTextures[4]->loadColorBuffer(IG1App::s_ig1app.getWinWidth(), IG1App::s_ig1app.getWinHeight()); 

	gTextures.push_back(new Texture()); //5
	gTextures[5]->load("../Bmps/windowV.bmp", 180); //5 textura translucida

	//modificamos el atributo del objeto
	estrella3D_->setTexure(gTextures[0]);

	cajaT_->setTexure(gTextures[1]); //la caja tiene dos texturas. 
	cajaT_->setIntTex(gTextures[2]);
	suelo_->setTexure(gTextures[3]);
	caja_fondo_->setTexure(gTextures[2]);
	foto_->setTexure(gTextures[4]);
	cristalera_->setTexure(gTextures[5]);

	//Transforms
	//posicion en -x,-z  (estrella, caja, fondoCaja)
	GLdouble x_ = -200.0, z_ = -200.0;
	estrella3D_->setX(x_); estrella3D_->setZ(z_); //en Entity::EstrellaTextura.update() se actualizan posiciones. 

	estrella3D_->setModelMat(translate(estrella3D_->modelMat(), dvec3(x_, estrH_, z_)));
	suelo_->setModelMat(translate(suelo_->modelMat(), dvec3(0.0, 0.0, -91.0)));
	cajaT_->setModelMat(translate(cajaT_->modelMat(), dvec3(x_, 0.0, z_)));
	caja_fondo_->setModelMat(translate(caja_fondo_->modelMat(), dvec3(x_, -z_, -90))); //z en y porque está rotado pivote en su propio eje
	foto_->setModelMat(translate(foto_->modelMat(), dvec3(200, 0.0, -90)));

	cristalera_->setModelMat(translate(cristalera_->modelMat(), dvec3(0.0, 120.0, 0.0)));
	cristalera_->setModelMat(scale(cristalera_->modelMat(), dvec3(1, 0.5, 1)));


	
	//Entities
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(estrella3D_);
	gObjects.push_back(cajaT_);
	gObjects.push_back(suelo_);
	gObjects.push_back(caja_fondo_);
	gObjects.push_back(foto_);
	gObjects.push_back(cristalera_);
}
//-------------------------------------------------------------------------