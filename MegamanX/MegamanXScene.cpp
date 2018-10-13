#include "MegamanXScene.h"
#include "Megaman.h"


void MegamanXScene::init()
{
	map.init("Data\\Map\\map.png", "Data\\Map\\objectsMap.txt","Data\\Map\\quadtree.txt");
}

void MegamanXScene::update()
{
	map.update();
}

void MegamanXScene::draw()
{
	map.draw();
	MEGAMAN->draw();
}

MegamanXScene::MegamanXScene()
{
}


MegamanXScene::~MegamanXScene()
{
}
