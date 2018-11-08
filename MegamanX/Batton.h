#pragma once
#include"Enemy.h"

enum BATTON_ACTION {
	BA_FLY,
	BA_ATTACK
};

class Batton:public Enemy
{
public:
	bool canAttack;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject* obj);

	Batton();
	~Batton();
};

