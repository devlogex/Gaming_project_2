#pragma once
#include"Enemy_Bullet.h"

class Batton_Bullet: public Enemy_Bullet
{
public:
	Enemy *enemy; // khong duoc xoa enemy nay trong destructor
	bool block;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);


	Batton_Bullet(Enemy*enemy);
	~Batton_Bullet();
};

