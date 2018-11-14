#pragma once
#include "Scene.h"
#include"Map.h"
#include"Sprite.h"

class MegamanXScene :	public Scene
{
public:
	static MegamanXScene* megamanXScene;

	Map map;

	void init();
	void update();
	void draw();

	MegamanXScene();
	~MegamanXScene();
};

