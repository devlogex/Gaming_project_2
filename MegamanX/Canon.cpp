#include "Canon.h"
#include"Megaman.h"
#include"Enemy_Bullet.h"
#include"Canon_Bullet.h"
#include"Stage.h"

void Canon::update()
{
	if (Stage::updating)
		return;
	if (!alive)
		return;

	timeBulletAppear.canCreateFrame();
	//update direction, animation
	if (MEGAMAN->top() < bottom() && MEGAMAN->bottom() > top() && MEGAMAN->x >= x)
	{
		direction = Right;
	}
	if (MEGAMAN->top() < bottom() && MEGAMAN->bottom() > top() && MEGAMAN->x < x)
	{
		direction = Left;
	}
	
	if (abs(MEGAMAN->x - x) <= VIEWPORT_WIDTH/2)
		changeAction(CA_ATTACK);
	else
		if (curAnimation != CA_RUN)
			changeAction(CA_RUN);

	//attack
	if (curAnimation == CA_ATTACK)
	{
		if (timeBulletAppear.isTerminated())
		{
			ENEMYBULLET->_Add(new Canon_Bullet(this));
			timeBulletAppear.start();
		}
	}

	//update vx
	if (curAnimation == CA_RUN)
		vx = direction * ENEMY_VX_GO;
	else
		if (curAnimation == CA_ATTACK)
			vx = 0;

	//update before handle
	Enemy::update();
}


void Canon::onCollision(BaseObject * other, int nx, int ny)
{
	Enemy::onCollision(other, nx, ny);

	if (other->collisionType == CT_GROUND && nx != 0)
		direction = (Direction)nx;

}

void Canon::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	life = CANON_LIFE;
}

Canon::Canon()
{
	sprite = SPRITEMANAGER->sprites[SPR_CANON];
	damage = ENEMY_DAMAGE;
	life = 10;
	alive = true;
	width = 42;
	height = 40;

	timeBulletAppear.init(0.8, 1);
	timeBulletAppear.start();
}


Canon::~Canon()
{
}
