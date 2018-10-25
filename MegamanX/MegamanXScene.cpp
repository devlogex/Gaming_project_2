#include "MegamanXScene.h"
#include "Megaman.h"
#include"Weapon.h"
#include"Weapon_Status.h"
#include"Enemy_Bullet.h"

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
	for (int i = 0; i < WEAPON->size(); i++)
		WEAPON->at(i)->draw();
	WEAPONSTATUS->draw();
	for (int i = 0; i < ENEMYBULLET->size(); i++)
	{
		ENEMYBULLET->at(i)->draw();
	}
}

MegamanXScene::MegamanXScene()
{
}


MegamanXScene::~MegamanXScene()
{
}
