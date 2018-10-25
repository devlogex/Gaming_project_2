#include "Enemy_Bullet.h"
#include"Enemy_Bullet_Location.h"
#include"Map.h"

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

	updateLocation();
}

void Enemy_Bullet::draw()
{
	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	int trucQuay = xInViewport;

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame,true);

}

void Enemy_Bullet::updateLocation()
{
	x += dx;
	y += dy;
}

void Enemy_Bullet::onAABBCheck(BaseObject * other)
{
	if (other->collisionType == CT_PLAYER)
		ENEMYBULLET->_Remove(this);
}

Enemy_Bullet::Enemy_Bullet(Enemy* enemy)
{
	
}


Enemy_Bullet::~Enemy_Bullet()
{
}
