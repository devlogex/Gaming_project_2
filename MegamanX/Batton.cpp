#include "Batton.h"
#include"Megaman.h"
#include"Enemy_Bullet.h"
#include"Batton_Bullet.h"
#include"Map.h"

void Batton::update()
{
	if (Stage::updating)
		return;
	if (!alive)
		return;

	//attack
	if (MEGAMAN->xCenter() > left() && MEGAMAN->left() < right() && curAnimation == BA_FLY && canAttack)
	{
		changeAction(BA_ATTACK);
		canAttack = false;
	}

	if (curAnimation == BA_ATTACK && curFrame == sprite->animates[BA_ATTACK].nFrame - 1)
	{
		changeAction(BA_FLY);
	}

	//update vx
	if (curAnimation == BA_FLY)
		vx = -ENEMY_VX_GO;
	else
		if (curAnimation == BA_ATTACK)
			vx = 0;

	//update before handle
	Enemy::update();

	//ReUpdate dy
	dy = 0;
}

void Batton::draw()
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
	else 
	{
		int xInViewport, yInViewport;
		Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

		int updateY = sprite->animates[curAnimation].frames[curFrame].height - height;
		yInViewport -= updateY;
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
	}
}

void Batton::onCollision(BaseObject * other, int nx, int ny)
{
	//////////////////////////////
}

void Batton::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	life = BATTON_LIFE;
	if(!canAttack)
		ENEMYBULLET->_Add(new Batton_Bullet(this));
	canAttack = true;
}

Batton::Batton()
{
	sprite = SPRITEMANAGER->sprites[SPR_BATTON];
	damage = ENEMY_DAMAGE;
	life = 10;
	alive = true;
	width = 42;
	height = 32;

	canAttack = true;

	// init batton_bullet
	ENEMYBULLET->_Add(new Batton_Bullet(this));
}


Batton::~Batton()
{
}
