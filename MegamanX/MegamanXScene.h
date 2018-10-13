#pragma once
#include "Scene.h"
#include"Map.h"
#include"Sprite.h"

class MegamanXScene :	public Scene
{
public:
	Map map;


	void init();
	void update();
	void draw();

	MegamanXScene();
	~MegamanXScene();
};

