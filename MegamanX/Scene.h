#pragma once
#include "Constant.h"

class Scene
{
public:
	static Scene* curScene;

	static void changeScene(Scene* scene, bool clean = true, bool isInit = true);
	virtual void init();
	virtual void update();
	virtual void draw();

	Scene();
	~Scene();
};
