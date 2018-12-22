#include "BlastHornet_Wing.h"
#include"BlastHornet_Wing_Location.h"
#include"BlastHornet.h"
#include"Map.h"


BlastHornet_Wing*BlastHornet_Wing::instance = 0;
BlastHornet_Wing * BlastHornet_Wing::getInstance()
{
	if (instance == 0)
		instance = new BlastHornet_Wing();
	return instance;
}

void BlastHornet_Wing::update()
{
	if (delayAnimation.canCreateFrame())
		curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
}

void BlastHornet_Wing::draw()
{
	if (!BLASTHORNET->alive)
		return;

	x = BLASTHORNET->x;
	y = BLASTHORNET->y;

	x -= sprite->animates[curAnimation].frames[curFrame].width/2;
	y -= sprite->animates[curAnimation].frames[curFrame].height;

	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(xCenter(), yCenter(), xInViewport, yInViewport);
	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
}

void BlastHornet_Wing::restore(BaseObject * obj)
{
}

void BlastHornet_Wing::release()
{
	delete instance;
	instance = 0;
	BLASTHORNET_WING_LOCATION->release();
}

BlastHornet_Wing::BlastHornet_Wing()
{
	sprite = SPRITEMANAGER->sprites[SPR_BLASTHORNET_WING];
	width = 47;
	height = 41;
}


BlastHornet_Wing::~BlastHornet_Wing()
{
}
