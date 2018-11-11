#include "BloodBoss.h"
#include"Boss.h"

BloodBoss* BloodBoss::instance = 0;
BloodBoss * BloodBoss::getInstance()
{
	if (instance == 0)
		instance = new BloodBoss();
	return instance;
}

BloodBoss::BloodBoss()
{
	sprite = SPRITEMANAGER->sprites[SPR_BLOOD_BOSS];
}

void BloodBoss::update()
{
	if (BOSS->life > 0 && BOSS->life <= BOSS_LIFE)
		curFrame = sprite->animates[0].nFrame - ((float)BOSS->life / (float)BOSS_LIFE)*sprite->animates[0].nFrame;
	else
		if (BOSS->life <= 0)
			curFrame = sprite->animates[0].nFrame - 1;
		else
			if (BOSS->life > BOSS_LIFE)
			{
				BOSS->life = BOSS_LIFE;
				curFrame = 0;
			}
}

void BloodBoss::draw()
{
	sprite->draw(VIEWPORT_WIDTH-30, 10, 0, curFrame);
}

void BloodBoss::restore(BaseObject * obj)
{
	sprite = SPRITEMANAGER->sprites[SPR_BLOOD_BOSS];
	curAnimation = 0;
	nextAnimation = 0;
	curFrame = 0;
}



BloodBoss::~BloodBoss()
{
}
