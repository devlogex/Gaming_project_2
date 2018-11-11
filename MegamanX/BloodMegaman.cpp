#include "BloodMegaman.h"
#include"Megaman.h"

BloodMegaman* BloodMegaman::instance = 0;
BloodMegaman * BloodMegaman::getInstance()
{
	if (instance == 0)
		instance = new BloodMegaman();
	return instance;
}

BloodMegaman::BloodMegaman()
{
	sprite = SPRITEMANAGER->sprites[SPR_BLOOD_MEGAMAN];
}

void BloodMegaman::update()
{
	Blood::update();
	if (MEGAMAN->life > 0 && MEGAMAN->life <= MEGAMAN_LIFE)
		curFrame = sprite->animates[0].nFrame - ((float)MEGAMAN->life / (float)MEGAMAN_LIFE)*sprite->animates[0].nFrame;
	else
		if (MEGAMAN->life <= 0)
			curFrame = sprite->animates[0].nFrame - 1;
		else
			if (MEGAMAN->life > MEGAMAN_LIFE)
			{
				MEGAMAN->life = MEGAMAN_LIFE;
				curFrame = 0;
			}
}

void BloodMegaman::draw()
{
	sprite->draw(10, 10, 0, curFrame);
}

void BloodMegaman::restore(BaseObject * obj)
{
	sprite = SPRITEMANAGER->sprites[SPR_BLOOD_MEGAMAN];
	curAnimation = 0;
	nextAnimation = 0;
	curFrame = 0;
}

BloodMegaman::~BloodMegaman()
{
}
