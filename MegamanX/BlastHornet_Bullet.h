#pragma once
#include"Enemy_Bullet.h"


class BlastHornet_Bullet:public Enemy_Bullet
{
public:
	GameTimeLoop timeDeath;
	bool isDirectBullet;
	GameTimeLoop timeLife;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	BlastHornet_Bullet(float vx,float vy,bool isDirectBullet=false);
	~BlastHornet_Bullet();
};

