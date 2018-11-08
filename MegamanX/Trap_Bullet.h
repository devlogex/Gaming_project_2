#pragma once
#include"Enemy_Bullet.h"

class Trap_Bullet:public Enemy_Bullet
{
public:
	void update();

	Trap_Bullet(Enemy*enemy);
	~Trap_Bullet();
};

