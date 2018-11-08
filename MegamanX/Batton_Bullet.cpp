#include "Batton_Bullet.h"
#include"Enemy_Bullet_Location.h"
#include"Batton.h"
#include"Map.h"

void Batton_Bullet::update()
{
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

		int updateY = enemy->sprite->animates[curAnimation].frames[curFrame].height - enemy->height;

		x = enemy->x + xInSprite;
		y = enemy->y - updateY + yInSprite;

		vx = enemy->vx;
		vy = 0;

	}
}


void Batton_Bullet::draw()
{
	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	int trucQuay = xInViewport;

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
}

void Batton_Bullet::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_GROUND)
		ENEMYBULLET->_Remove(this);
}


Batton_Bullet::Batton_Bullet(Enemy*enemy)
{
	this->enemy = enemy;
	damage = 20;
	sprite = SPRITEMANAGER->sprites[SPR_BATTON_BULLET];

	collisionType = CT_ENEMY;
	allowDelete = false;

	int xInSprite = ENEMYBULLETLOCATION->ptsBatton[enemy->curFrame].x;
	int yInSprite = ENEMYBULLETLOCATION->ptsBatton[enemy->curFrame].y;

	int updateY = enemy->sprite->animates[curAnimation].frames[curFrame].height - enemy->height;

	x = enemy->x + xInSprite;
	y = enemy->y - updateY + yInSprite;

	vx = enemy->vx;
	vy = 0;

	block = true;
}


Batton_Bullet::~Batton_Bullet()
{
}
