#include "BloodBlastHornet.h"
#include"Stage.h"
#include"BlastHornet.h"


BloodBlastHornet * BloodBlastHornet::instance = 0;
BloodBlastHornet * BloodBlastHornet::getInstance()
{
	if (instance == 0)
		instance = new BloodBlastHornet();
	return instance;
}
BloodBlastHornet::BloodBlastHornet()
{
	sprite = SPRITEMANAGER->sprites[SPR_BLOOD_BLASTHORNET];
}

void BloodBlastHornet::update()
{
	if (Stage::curStage->index != 4)
		return;
	if (BLASTHORNET->life > 0 && BLASTHORNET->life <= BLASTHORNET_LIFE)
		curFrame = sprite->animates[0].nFrame - ((float)BLASTHORNET->life / (float)BLASTHORNET_LIFE)*sprite->animates[0].nFrame;
	else
		if (BLASTHORNET->life <= 0)
			curFrame = sprite->animates[0].nFrame - 1;
		else
			if (BLASTHORNET->life > BLASTHORNET_LIFE)
			{
				BLASTHORNET->life = BLASTHORNET_LIFE;
				curFrame = 0;
			}
}

void BloodBlastHornet::draw()
{
	/*if (Stage::curStage->index != 4)
		return;
	sprite->draw(VIEWPORT_WIDTH - 30, 10, 0, curFrame);*/
}

void BloodBlastHornet::restore(BaseObject * obj)
{
	sprite = SPRITEMANAGER->sprites[SPR_BLOOD_BLASTHORNET];
	curAnimation = 0;
	nextAnimation = 0;
	curFrame = 0;
}


BloodBlastHornet::~BloodBlastHornet()
{
}
