#include "Enemy.h"
#include"Map.h"
#include"Weapon.h"
#include"Stage.h"
#include"GameSound.h"

void Enemy::update()
{
	if (!alive)
		return;
	if (Stage::curStage->updating)
		return;
	MovableObject::update();
}

void Enemy::updateLocation()
{
	if (!alive)
		return;
	if (Stage::curStage->updating)
		return;

	x += dx;
	y += dy;
}

void Enemy::draw()
{
	if (!alive)
	{
		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_DELETEOBJECT];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 8;
		}

		if (timeDeath.isTerminated())
		{
			GAMESOUND->stop(AUDIO_CREP_DIE);
			return;
		}

		int xInViewport, yInViewport;
		Map::curMap->convertToViewportPos(xCenter(), yCenter(), xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame, true);

		return;
	}

	MovableObject::draw();
}

void Enemy::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
}

void Enemy::onAABBCheck(BaseObject * other)
{
	if (other->collisionType == CT_WEAPON)
	{
		Weapon* wp = (Weapon*)other;
		life -= wp->damage;
		if (life <= 0)
		{
			alive = false;
			GAMESOUND->play(AUDIO_CREP_DIE,true);
		}
	}
}

void Enemy::restore(BaseObject * obj)
{
	DrawableObject::restore(obj);
	timeDeath.start();
	vx = 0;
	vy = 0;
	dx = 0;
	dy = 0;
}

Enemy::Enemy()
{
	timeDeath.init(0.3, 7);
	timeDeath.start();
	collisionType = CT_ENEMY;
	direction = Left;
}


Enemy::~Enemy()
{
}
