#include "Batton_Bullet.h"
#include"Enemy_Bullet_Location.h"
#include"Batton.h"
#include"Map.h"

void Batton_Bullet::update()
{
	if (allowDelete)
	{
		vx = 0;
		vy = 0;
		dx = 0;
		dy = 0;
		return;
	}

	if (!enemy->alive)
	{
		ENEMYBULLET->_Remove(this);
		((Batton*)enemy)->canAttack = false;
		return;
	}
	if (enemy->curAnimation == BA_ATTACK)
		block = false;
	if (!block)
	{
		vx = 0;
		vy = 100;
		MovableObject::update();
	}
	else
	{
		int xInSprite = ENEMYBULLETLOCATION->ptsBatton[enemy->curFrame].x;
		int yInSprite = ENEMYBULLETLOCATION->ptsBatton[enemy->curFrame].y;

		int updateY = enemy->sprite->animates[enemy->curAnimation].frames[enemy->curFrame].height - enemy->height;

		x = enemy->x + xInSprite;
		y = enemy->y - updateY + yInSprite;

		vx = enemy->vx;
		vy = 0;

	}

	if (((Batton*)enemy)->canAttack)
		if (timeDelay.isTerminated())
		{
			curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
			timeDelay.start();
		}
		else
			timeDelay.canCreateFrame();

}


void Batton_Bullet::draw()
{
	if (allowDelete)
	{
		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_DELETEOBJECT];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 8;
		}

		if (timeDeath.isTerminated())
		{
			ENEMYBULLET->_Remove(this);
			return;
		}

		int xInViewport, yInViewport;
		Map::curMap->convertToViewportPos(xCenter(), yCenter(), xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame, true);

		return;
	}

	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
}

void Batton_Bullet::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_GROUND)
		allowDelete = true;
}


void Batton_Bullet::onAABBCheck(BaseObject * other)
{
	if ((other->collisionType == CT_PLAYER && !MEGAMAN->inviolable) || (other->collisionType == CT_GROUND))
		allowDelete = true;
}

Batton_Bullet::Batton_Bullet(Enemy*enemy)
{
	this->enemy = enemy;
	damage = BATTON_BL_DAMAGE;
	sprite = SPRITEMANAGER->sprites[SPR_BATTON_BULLET];

	collisionType = CT_ENEMY;
	allowDelete = false;

	int xInSprite = ENEMYBULLETLOCATION->ptsBatton[enemy->curFrame].x;
	int yInSprite = ENEMYBULLETLOCATION->ptsBatton[enemy->curFrame].y;

	int updateY = enemy->sprite->animates[enemy->curAnimation].frames[enemy->curFrame].height - enemy->height;

	x = enemy->x + enemy->width - xInSprite;
	y = enemy->y - updateY + yInSprite;

	vx = enemy->vx;
	vy = 0;

	block = true;

	timeDelay.init(0.1, 2);
	timeDelay.start();
	timeDeath.init(0.2, 5);
	timeDeath.start();
}


Batton_Bullet::~Batton_Bullet()
{
}
