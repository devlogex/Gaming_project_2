#include "Trap_Bullet.h"
#include"Enemy_Bullet_Location.h"
#include"Megaman.h"
#include"Map.h"

void Trap_Bullet::update()
{
	curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
}

Trap_Bullet::Trap_Bullet(Enemy*enemy)
{
	damage = 10;
	sprite = SPRITEMANAGER->sprites[SPR_TRAP_BULLET];

	collisionType = CT_ENEMY;
	allowDelete = false;

	int xInSprite = ENEMYBULLETLOCATION->ptsTrap[0].x;
	int yInSprite = ENEMYBULLETLOCATION->ptsTrap[0].y;

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

	vx = MEGAMAN->xCenter() - x;
	vy = MEGAMAN->yCenter() - y;

	dx = vx * GAME_TIME->frameTime;
	dy = vy * GAME_TIME->frameTime;
}


Trap_Bullet::~Trap_Bullet()
{
}
