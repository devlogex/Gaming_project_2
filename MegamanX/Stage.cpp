#include "Stage.h"
#include "Map.h"
#include "Camera.h"
#include"Megaman.h"
#include"Door.h"
#include"QuadTree.h"
#include"Enemy_Bullet.h"
#include"Weapon.h"
#include"Genjibo_SP.h"
#include"Genjibo.h"
#include"BlastHornet.h"

List<Stage*>* Stage::curStages = 0;
Stage* Stage::curStage = 0;
bool Stage::updating = false;
Stage::Stage(fstream & fs, int index)
{
	fs >> x >> y >> width >> height >> xPre >> yPre;
	this->index = index;
}

void Stage::update()
{
	if (!updating)
		return;

	if (CAMERA->x >= curStage->x)
		updating = false;
}

void Stage::loadStageNext()
{
	curStage = curStages->at(curStage->index + 1);
	updating = true;
}

void Stage::loadStagePrev()
{
	for (int i = 0; i < ENEMYBULLET->size(); i++)
		if (ENEMYBULLET->at(i)->enemy->id % 10 != 2)
		{
			ENEMYBULLET->_Remove(ENEMYBULLET->at(i));
			i--;
		}

	for (int i = 0; i < WEAPON->size(); i++)
	{
		WEAPON->_Remove(WEAPON->at(i));
		i--;
	}

	CAMERA->x = curStage->xPre;
	CAMERA->y = curStage->yPre;
	Map::curMap->quadtree.update();

	Map::curMap->xMap = curStage->xPre;
	Map::curMap->yMap = curStage->yPre;
	MEGAMAN->x = CAMERA->xCenter() - MEGAMAN->width;
	MEGAMAN->y = CAMERA->yCenter();
	MEGAMAN->restore(MEGAMAN);
	for (int i = 0; i < Door::doors->size(); i++)
		Door::doors->at(i)->restore(Door::doors->at(i));

	if (Stage::curStage->index == 1)
	{
		GENJIBO_SP->x = GENJIBO_SP->oldX;
		GENJIBO_SP->y = GENJIBO_SP->oldY;
		GENJIBO_SP->restore(GENJIBO_SP);
		GENJIBO_SP->isActive = true;
		GENJIBO->x = GENJIBO->oldX;
		GENJIBO->y = GENJIBO->oldY;
		GENJIBO->restore(GENJIBO);
	}
	if (Stage::curStage->index == 4)
	{
		BLASTHORNET->x=BLASTHORNET->oldX;
		BLASTHORNET->y = BLASTHORNET->oldY;

		BLASTHORNET->restore(BLASTHORNET);
	}
}


Stage::~Stage()
{
}
