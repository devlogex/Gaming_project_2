#include "Canon_Bullet.h"
#include"SpriteManager.h"
#include"Enemy_Bullet_Location.h"

Canon_Bullet::Canon_Bullet(Enemy* enemy)
{
	damage = 10;
	sprite = SPRITEMANAGER->sprites[SPR_CANON_BULLET];

	collisionType = CT_ENEMY;
	allowDelete = false;

	direction = enemy->direction;

	vx = WEAPON_VX * direction;
	vy = 0;

	int xInSprite = enemy->id % 100 == SPR_CANON ? ENEMYBULLETLOCATION->ptsCanon[enemy->curFrame].x : 0;
	int yInSprite = enemy->id % 100 == SPR_CANON ? ENEMYBULLETLOCATION->ptsCanon[enemy->curFrame].y : 0;

	int updateY = enemy->sprite->animates[curAnimation].frames[curFrame].height - enemy->height;

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


Canon_Bullet::~Canon_Bullet()
{
}
