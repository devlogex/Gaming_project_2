#include "Stage.h"
#include "Map.h"
#include "Camera.h"
#include"Megaman.h"
#include"Door.h"
#include"QuadTree.h"
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
	Map::curMap->quadtree.removeObjectFromCamera();
	CAMERA->x = curStage->xPre;
	CAMERA->y = curStage->yPre;
	Map::curMap->xMap = curStage->xPre;
	Map::curMap->yMap = curStage->yPre;
	MEGAMAN->x = CAMERA->xCenter() - MEGAMAN->width;
	MEGAMAN->y = CAMERA->yCenter();
	MEGAMAN->restore(MEGAMAN);
	for (int i = 0; i < Door::doors->size(); i++)
		Door::doors->at(i)->restore(Door::doors->at(i));
}


Stage::~Stage()
{
}
