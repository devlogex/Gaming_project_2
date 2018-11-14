#include "Enemy_Bullet.h"
#include"Enemy_Bullet_Location.h"
#include"Map.h"
#include"Megaman.h"
#include"Camera.h"

List<Enemy_Bullet*>* Enemy_Bullet::enemyBullets = 0;
List<Enemy_Bullet*>* Enemy_Bullet::getEnemyBullets()
{
	if (enemyBullets == 0)
		enemyBullets = new List<Enemy_Bullet*>();
	return enemyBullets;
}

void Enemy_Bullet::update()
{
	dx = vx * GAME_TIME->frameTime;
	dy = 0;
}

void Enemy_Bullet::draw()
{
	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame,true);
}

void Enemy_Bullet::updateLocation()
{
	x += dx;
	y += dy;

	if ((x > CAMERA->right() || x < CAMERA->left()) && enemy->id % 7 != 2)
		ENEMYBULLET->_Remove(this);
	if ((y > CAMERA->bottom() || y < CAMERA->top()) && enemy->id % 7 != 2)
		ENEMYBULLET->_Remove(this);
}

void Enemy_Bullet::onAABBCheck(BaseObject * other)
{
	if (other->collisionType == CT_PLAYER)
		if (!MEGAMAN->inviolable)
			ENEMYBULLET->_Remove(this);
}

void Enemy_Bullet::onCollision(BaseObject * other, int nx, int ny)
{
}

Enemy_Bullet::Enemy_Bullet(Enemy* enemy)
{
	id = -5;
}

Enemy_Bullet::~Enemy_Bullet()
{
}
