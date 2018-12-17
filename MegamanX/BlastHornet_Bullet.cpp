#include "BlastHornet_Bullet.h"
#include"Map.h"
#include"Enemy_Bullet_Location.h"
#include"BlastHornet.h"
#include"Megaman.h"

void BlastHornet_Bullet::update()
{
	if (delayAnimation.canCreateFrame())
		curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;

	if (isDirectBullet)
	{
		vx = MEGAMAN->xCenter() - x;
		vy = MEGAMAN->yCenter() - y;
		BLASTHORNET->fixV(vx, vy, 30);
	}

	if (timeLife.isTerminated())
		allowDelete = true;
	else
		timeLife.canCreateFrame();
	if (allowDelete)
	{
		vx = 0;
		vy = 0;
	}
	dx = vx * GAME_TIME->frameTime;
	dy = vy * GAME_TIME->frameTime;

	if (!enemy->alive)
		ENEMYBULLET->_Remove(this);
}

void BlastHornet_Bullet::draw()
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

	MovableObject::draw();
}

void BlastHornet_Bullet::onCollision(BaseObject * other, int nx, int ny)
{
	if (!isDirectBullet && other->collisionType==CT_GROUND)
	{
		MovableObject::onCollision(other, nx, ny);
		vx = 0;
		vy = 0;
	}
}

void BlastHornet_Bullet::onAABBCheck(BaseObject * other)
{
	if (other->collisionType == CT_WEAPON || other->collisionType==CT_PLAYER)
		allowDelete = true;
}

BlastHornet_Bullet::BlastHornet_Bullet(float vx, float vy, bool isDirectBullet)
{
	sprite = SPRITEMANAGER->sprites[SPR_BLASTHORNET_BULLET];
	collisionType = CT_ENEMY;
	damage = BLASTHORNET_BULLET_DAMAGE;
	timeDeath.init(0.2, 4);
	timeDeath.start();
	timeLife.init(0.4, 10);
	timeLife.start();
	width = 19;
	height = 20;

	allowDelete = false;
	this->isDirectBullet = isDirectBullet;


	int xInSprite = ENEMYBULLETLOCATION->ptsTrap[0].x;
	int yInSprite = ENEMYBULLETLOCATION->ptsTrap[0].y;

	enemy = BLASTHORNET;
	direction = enemy->direction;

	int updateY = enemy->sprite->animates[enemy->curAnimation].frames[enemy->curFrame].height - enemy->height;

	if (direction == Left)
	{
		x = enemy->x + enemy->width - xInSprite;
		y = enemy->y - updateY + yInSprite;
	}
	else
	{
		x = enemy->x + xInSprite;
		y = enemy->y - updateY + yInSprite;
	}

	if (isDirectBullet)
	{
		this->vx = MEGAMAN->xCenter() - x;
		this->vy = MEGAMAN->yCenter() - y;
		BLASTHORNET->fixV(this->vx, this->vy,30);

	}
	else
	{
		this->vx = vx*enemy->direction;
		this->vy = vy;
	}

}

BlastHornet_Bullet::~BlastHornet_Bullet()
{
}
