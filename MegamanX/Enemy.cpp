#include "Enemy.h"
#include"Map.h"
#include"Weapon.h"

void Enemy::update()
{
	MovableObject::update();
}

void Enemy::draw()
{
	if (!alive)
	{
		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_DELETEOBJECT];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 6;
		}

		if (timeDeath.isTerminated())
			return;

		int xInViewport, yInViewport;
		Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
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
			alive = false;

	}
}

void Enemy::restore(BaseObject * obj)
{
	DrawableObject::restore(obj);
	timeDeath.start();
}

Enemy::Enemy()
{
	timeDeath.init(0.2, 10);
	timeDeath.start();
	collisionType = CT_ENEMY;
}


Enemy::~Enemy()
{
}
