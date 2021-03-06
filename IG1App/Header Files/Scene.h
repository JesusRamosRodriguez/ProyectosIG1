//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

	void update();

    void render(Camera const& cam) const;

	void setState(int id);
	
protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;

private:
	int mId_ = 1;	//identificador para la escena

	void scene2D(); //Enunciado P0. EJERCICIOS P1: [1-6)	//tecla: id = 0
	void scene3D();	//Enunciado P0. EJERCICIOS P1: [6-?)	//tecla: id = 1		
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

