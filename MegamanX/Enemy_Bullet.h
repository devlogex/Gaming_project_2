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

	virtual void update();
	virtual void draw();
	virtual void updateLocation();

	virtual void onAABBCheck(BaseObject* other);

	Enemy_Bullet(Enemy* enemy=0);
	~Enemy_Bullet();
};

