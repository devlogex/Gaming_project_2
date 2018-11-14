#include "MegamanXScene.h"
#include "Megaman.h"
#include"Weapon.h"
#include"Weapon_Status.h"
#include"Enemy_Bullet.h"
#include"MainScreen.h"
#include"Boss.h"

MegamanXScene* MegamanXScene::megamanXScene = 0;
void MegamanXScene::init()
{
	map.init("Data\\Map\\map\\map.png", "Data\\Map\\map\\objectsMap.txt","Data\\Map\\map\\quadtree.txt");
	map.initStage("Data\\Map\\map\\stage.txt");
}

void MegamanXScene::update()
{
	if (MEGAMAN->numberOfAlive == 0 || !BOSS->alive)
	{
		Scene::changeScene(new MainScreen(),false);
		MEGAMAN->numberOfAlive = 3;
		return;
	}
	if (!MEGAMAN->alive)
	{
		if (Stage::curStage->index == Stage::curStages->size() - 1)
			Stage::curStage = Stage::curStages->at(Stage::curStage->index - 1);
		Stage::loadStagePrev();
		return;
	}

	map.update();
}

void MegamanXScene::draw()
{
	map.draw();
	MEGAMAN->draw();
	
}

MegamanXScene::MegamanXScene()
{
	megamanXScene = this;
}


MegamanXScene::~MegamanXScene()
{
}
