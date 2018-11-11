#include "Boss_Bullet.h"
#include"Enemy_Bullet_Location.h"
#include"Megaman.h"

void Boss_Bullet::update()
{
	Enemy_Bullet::update();
	curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
}


Boss_Bullet::Boss_Bullet(Enemy*enemy)
{
	damage = BOSS_BL_DAMAGE;
	sprite = SPRITEMANAGER->sprites[SPR_BOSS_BULLET];

	collisionType = CT_ENEMY;
	allowDelete = false;

	direction = enemy->direction;

	vx = ENEMY_BULLET_VX * direction;
	vy = 0;

	int xInSprite = ENEMYBULLETLOCATION->ptsBoss[0].x;
	int yInSprite = ENEMYBULLETLOCATION->ptsBoss[0].y;

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
}


Boss_Bullet::~Boss_Bullet()
{
}
