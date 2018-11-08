#include "Boss.h"
#include"Megaman.h"
#include"Boss_Bullet.h"


void Boss::update()
{
	updateVX();

	timeAttack.curLoop++;

	updateAnimation();

	updateBeforeHandle();
}

void Boss::updateAnimation()
{
	if (curAnimation == BA_STAND)
	{
		if (timeAction.curLoop > 100)
		{
			changeAction(BA_SHOOT);
			timeAction.start();
		}
		else
			timeAction.curLoop++;
	}
	else
		if (curAnimation == BA_SHOOT)
		{
			if (timeAction.curLoop>80)
			{
				changeAction(BA_PUSH);
				timeAction.start();
			}
			else
			{
				timeAction.curLoop++;
				if (curFrame == sprite->animates[curAnimation].nFrame - 1 && timeAttack.curLoop>25)
				{
					ENEMYBULLET->_Add(new Boss_Bullet(this));
					timeAttack.start();
				}
			}
		}

	if (life <= 50)
	{
		if (curAnimation == BA_PUSH)
		{
			if (MEGAMAN->right() > left() && MEGAMAN->left() < right())
			{
				changeAction(BA_HIT);
				if (MEGAMAN->x >= x)
					direction = Right;
				else
					direction = Left;
			}
		}
	}
}

void Boss::updateVX()
{
	if (curAnimation == BA_STAND || curAnimation == BA_SHOOT)
		vx = 0;
	else
		if (curAnimation == BA_PUSH || curAnimation == BA_HIT)
			vx = BOSS_VX * direction;
}

void Boss::updateBeforeHandle()
{
	if (!alive)
		return;

	isOnGround = false;
	updateVelocity();
	BaseObject::update();

	if (delayAnimation.canCreateFrame())
	{
		if (curAnimation != nextAnimation)
		{
			curAnimation = nextAnimation;
			curFrame = 0;
		}
		else
			if (curFrame++ >= sprite->animates[curAnimation].nFrame - 1)
			{
				if (curAnimation ==BA_STAND )
					curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
				else
					curFrame = sprite->animates[curAnimation].nFrame - 1;

			}
	}
}

void Boss::onCollision(BaseObject * other, int nx, int ny)
{
	Enemy::onCollision(other, nx, ny);

	if (other->collisionType == CT_GROUND && nx != 0)
	{
		direction = (Direction)nx;
		
			curAnimation = BA_STAND;
			nextAnimation = BA_STAND;
			curFrame = 0;
			timeAction.start();
		
	}
}

void Boss::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	life = 100;
}

Boss::Boss()
{
	sprite = SPRITEMANAGER->sprites[SPR_CANON];
	damage = 20;
	life = 100;
	alive = true;
	width = 60;
	height = 74;

	timeAttack.init(0.1, 5);
	timeAttack.start();

	timeAction.init(10, 1000);
	timeAction.start();
}


Boss::~Boss()
{
}
