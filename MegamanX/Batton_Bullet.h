#pragma once
#include"Enemy_Bullet.h"

class Batton_Bullet: public Enemy_Bullet
{
public:
	bool block;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);

	GameTimeLoop timeDelay;
	GameTimeLoop timeDeath;

	void onAABBCheck(BaseObject* other);

	Batton_Bullet(Enemy*enemy);
	~Batton_Bullet();
};

