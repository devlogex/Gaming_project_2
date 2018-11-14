#include "Scene.h"
#include"MegamanXScene.h"

Scene* Scene::curScene = 0;
void Scene::changeScene(Scene* scene, bool clean,bool isInit)
{
	if (curScene != 0 && clean)
		delete curScene;

	curScene = scene;
	if (isInit)
		curScene->init();
}

Scene::Scene(void)
{
}

void Scene::init()
{
}

void Scene::update()
{
}

void Scene::draw()
{
}

Scene::~Scene(void)
{
}
