#include "MegamanXScene.h"
#include "Megaman.h"
#include"Weapon.h"
#include"Weapon_Status.h"
#include"Enemy_Bullet.h"
#include"MainScreen.h"
#include"Boss.h"
#include"Genjibo_SP.h"

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
		timeDraw.canCreateFrame();
		if (!timeDraw.isTerminated())
			return;
		else
			timeDraw.start();

		Scene::changeScene(new MainScreen(), false);
		MEGAMAN->numberOfAlive = 3;
		if (Stage::curStage->index == Stage::curStages->size() - 1)
			Stage::curStage = Stage::curStages->at(Stage::curStage->index - 1);
		Stage::loadStagePrev();
		return;
	}
	if (!MEGAMAN->alive)
	{
		timeDraw.canCreateFrame();
		if (!timeDraw.isTerminated())
			return;
		else
			timeDraw.start();

		if (Stage::curStage->index == Stage::curStages->size() - 1)
			Stage::curStage = Stage::curStages->at(Stage::curStage->index - 1);
		Stage::loadStagePrev();
		return;
	}

	if (Stage::curStage->updating && 
		(Stage::curStage->index == 1 || Stage::curStage->index == 2 || Stage::curStage->index == 4 || Stage::curStage->index == 5))
	{
		timeDraw.canCreateFrame();
		if (!timeDraw.isTerminated())
			return;
		else
			timeDraw.start();

		Stage::loadStagePrev();
	}

	map.update();
}

void MegamanXScene::draw()
{
	if (timeDraw.curLoop > 0)
		return;

	map.draw();
	MEGAMAN->draw();
}

MegamanXScene::MegamanXScene()
{
	megamanXScene = this;
	timeDraw.init(0.3, 5);
	timeDraw.start();
}


MegamanXScene::~MegamanXScene()
{
}
