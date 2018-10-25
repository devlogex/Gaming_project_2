#pragma once
#include"Enemy_Bullet.h"

class Canon_Bullet:public Enemy_Bullet
{
public:

	Canon_Bullet(Enemy* enemy);
	~Canon_Bullet();
};

