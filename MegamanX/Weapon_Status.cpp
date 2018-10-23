#include "Weapon_Status.h"
#include"Megaman.h"
#include"Map.h"

Weapon_Status*Weapon_Status::instance = 0;
Weapon_Status * Weapon_Status::getInstance()
{
	if (instance == 0)
		instance = new Weapon_Status();
	return instance;
}
Weapon_Status::Weapon_Status()
{
	sprite = SPRITEMANAGER->sprites[SPR_WEAPON_STATUS];
	x = MEGAMAN->x + MEGAMAN->sprite->animates[MEGAMAN->curAnimation].frames[MEGAMAN->curFrame].width/2;
	y = MEGAMAN->y +MEGAMAN->updateY + MEGAMAN->sprite->animates[MEGAMAN->curAnimation].frames[MEGAMAN->curFrame].height/2;

	curAnimation = WS_MEDIUM;
	nextAnimation = WS_LARGE;
	allowDraw = false;
}

void Weapon_Status::update()
{
	if (allowDraw)
	{
		if (MEGAMAN->direction == Right)
			x = MEGAMAN->x + MEGAMAN->sprite->animates[MEGAMAN->curAnimation].frames[MEGAMAN->curFrame].width / 2;
		else
			x = MEGAMAN->x - MEGAMAN->sprite->animates[MEGAMAN->curAnimation].frames[MEGAMAN->curFrame].width / 2 + MEGAMAN->width;
		y = MEGAMAN->y - MEGAMAN->updateY + MEGAMAN->sprite->animates[MEGAMAN->curAnimation].frames[MEGAMAN->curFrame].height / 2;
		DrawableObject::update();
	}
	else
	{
		curAnimation = WS_MEDIUM;
		nextAnimation = WS_MEDIUM;
	}
}

void Weapon_Status::draw()
{
	if (!allowDraw)
		return;

	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame, true);

}


Weapon_Status::~Weapon_Status()
{
}
