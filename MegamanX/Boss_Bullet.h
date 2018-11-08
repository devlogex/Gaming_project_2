#pragma once
#include"Enemy_Bullet.h"
#include"Enemy.h"

class Boss_Bullet:public Enemy_Bullet
{
public:
	void update();
	Boss_Bullet(Enemy*enemy);
	~Boss_Bullet();
};

