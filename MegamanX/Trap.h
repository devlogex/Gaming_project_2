#pragma once
#include"Enemy.h"
enum TRAP_ACTION {
	TA_APPEAR,
	TA_ATTACK
};
class Trap:public Enemy
{
public:
	GameTimeLoop timeBulletAppear;

	void update();
	void draw();
	void restore(BaseObject* obj);

	Trap();
	~Trap();
};

