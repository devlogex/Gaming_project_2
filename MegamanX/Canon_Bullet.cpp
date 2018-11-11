#include "Canon_Bullet.h"
#include"SpriteManager.h"
#include"Enemy_Bullet_Location.h"

Canon_Bullet::Canon_Bullet(Enemy* enemy)
{
	damage = CANON_BL_DAMAGE;
	sprite = SPRITEMANAGER->sprites[SPR_CANON_BULLET];

	collisionType = CT_ENEMY;
	allowDelete = false;

	direction = enemy->direction;

	vx = ENEMY_BULLET_VX * direction;
	vy = 0;

	int xInSprite =  ENEMYBULLETLOCATION->ptsCanon[enemy->curFrame].x;
	int yInSprite =  ENEMYBULLETLOCATION->ptsCanon[enemy->curFrame].y;

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


Canon_Bullet::~Canon_Bullet()
{
}
