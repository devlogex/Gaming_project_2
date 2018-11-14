#pragma once
#include"MovableObject.h"
#include"List.h"
#include"Enemy.h"

class Enemy_Bullet:public MovableObject
{
public:
	static List<Enemy_Bullet*>*enemyBullets;
	static List<Enemy_Bullet*>*getEnemyBullets();

	int damage;
	Enemy* enemy;// khong duoc xoa enemy nay trong destructor

	virtual void update();
	virtual void draw();
	virtual void updateLocation();

	virtual void onAABBCheck(BaseObject* other);
	virtual void onCollision(BaseObject* other, int nx, int ny);

	Enemy_Bullet(Enemy* enemy=0);
	~Enemy_Bullet();
};

