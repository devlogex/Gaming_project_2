#include "Genjibo_SP.h"
#include"Genjibo.h"
#include"Stage.h"
#include"Map.h"
#include"Genjibo_SP_Engine.h"
#include"KeyGame.h"

Genjibo_SP* Genjibo_SP::instance = 0;
Genjibo_SP * Genjibo_SP::getInstance()
{
	if (instance == 0)
		instance = new Genjibo_SP();
	return instance;
}

void Genjibo_SP::update()
{
	if (!isActive)
		return;
	if (Stage::curStage->updating)
		return;

	updateVY();
	updateAnimation();
	updateBeforeHandle();

	if (!(y <= 580 && direction == Left))
		MEGAMAN->isActive = false;
	else
		MEGAMAN->isActive = true;

	GENJIBO_SP_ENGINE->update();
}

void Genjibo_SP::updateAnimation()
{
	if (y >= 686)
		changeAction(GSA_SHOT);
	if (curAnimation == GSA_SHOT && timeShot.isTerminated())
	{
		changeAction(GSA_FLY);
		direction = Left;
	}
	else
		timeShot.canCreateFrame();

}

void Genjibo_SP::updateVY()
{
	if (curAnimation == GSA_FLY) // Right== đi xuống, Left == đi lên
		vy = direction * GENJIBO_SP_VY;
	else
		vy = 0;
}

void Genjibo_SP::updateBeforeHandle()
{
	dx = 0;
	dy = vy * GAME_TIME->frameTime;
	if (delayAnimation.canCreateFrame())
	{
		if (curAnimation != nextAnimation)
		{
			curAnimation = nextAnimation;
			curFrame = 0;
		}
		else
			curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
	}
}

void Genjibo_SP::updateLocation()
{
	if (!isActive)
		return;
	if (Stage::curStage->updating)
		return;

	x += dx;
	y += dy;
}

void Genjibo_SP::draw()
{
	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);

	GENJIBO_SP_ENGINE->draw();
}

void Genjibo_SP::onCollision(BaseObject * other, int nx, int ny)
{
}

void Genjibo_SP::onAABBCheck(BaseObject * other)
{
}

void Genjibo_SP::restore(BaseObject * obj)
{
	DrawableObject::restore(obj);
	isActive = false;
	direction = Right;
	timeShot.start();

	GENJIBO_SP_ENGINE->release();
}

void Genjibo_SP::release()
{
	delete instance;
	instance = 0;
}

Genjibo_SP::Genjibo_SP()
{
	sprite = SPRITEMANAGER->sprites[SPR_GENJIBO_SP];
	damage = 0;
	life = 10;
	alive = true;
	width = 22;
	height = 22;
	x = 4219;
	y = 580;

	direction = Right;// Right== đi xuống, Left == đi lên
	vx = 0;
	isActive = true;
	timeShot.init(0.3, 5);
	timeShot.start();
}

Genjibo_SP::~Genjibo_SP()
{
}
