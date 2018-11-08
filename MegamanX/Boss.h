#pragma once
#include"Enemy.h"

enum BOSS_ACTION {
	BA_STAND,
	BA_PUSH,
	BA_SHOOT,
	BA_HIT
};
class Boss:public Enemy
{
public:
	GameTimeLoop timeAttack;
	GameTimeLoop timeAction;

	void update();
	void updateAnimation();
	void updateVX();
	void updateBeforeHandle();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject* obj);
	   	 
	Boss();
	~Boss();
};

