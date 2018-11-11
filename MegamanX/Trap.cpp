#include "Trap.h"
#include"Enemy_Bullet.h"
#include"Trap_Bullet.h"

void Trap::update()
{
	if (!alive)
		return;
	   
	if(curAnimation==TA_APPEAR)
		if (curFrame == sprite->animates[curAnimation].nFrame-1)
		{
			curAnimation = TA_ATTACK;
			curFrame = 0;
		}
	if (curAnimation == TA_ATTACK && curFrame == sprite->animates[curAnimation].nFrame - 1)
	{
		if (timeBulletAppear.canCreateFrame())
		{
			ENEMYBULLET->_Add(new Trap_Bullet(this));
			timeBulletAppear.start();
		}
	}
	curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
	
}

void Trap::draw()
{
	Enemy::draw();
}

void Trap::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	life = 10;
}

Trap::Trap()
{
	sprite = SPRITEMANAGER->sprites[SPR_TRAP];
	damage = ENEMY_DAMAGE;
	life = 10;
	alive = true;
	width = 41;
	height = 31;

	vx = 0;
	vy = 0;
	dx = 0;
	dy = 0;

	timeBulletAppear.init(3, 300);
	timeBulletAppear.start();
}


Trap::~Trap()
{
}
