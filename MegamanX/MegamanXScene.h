#pragma once
#include "Scene.h"
#include"Map.h"
#include"Sprite.h"

class MegamanXScene :	public Scene
{
public:
	static MegamanXScene* megamanXScene;

	Map map;
	GameTimeLoop timeDraw;

	void init();
	void update();
	void draw();
	void release();

	MegamanXScene();
	~MegamanXScene();
};

