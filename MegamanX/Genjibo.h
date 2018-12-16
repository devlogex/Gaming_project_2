#pragma once
#include"Enemy.h"
#include"Point.h"

enum GENJIBO_ACTION {
	GA_APPEAR,
	GA_ROLL_STAND,
	GA_ROLL_RUN,
	GA_RUN,
	GA_ROTARY_STAND,
	GA_ROTARY_RUN,
	GA_DAMAGED
};
class Genjibo:public Enemy
{
private:
	static Genjibo*instance;
	Genjibo();

public:
	static Genjibo*getInstance();

	GameTimeLoop timeAppear;
	GameTimeLoop timeRollStand;
	GameTimeLoop timeRollRun;
	GameTimeLoop timeRotaryStand;
	GameTimeLoop timeRotaryRun;
	GameTimeLoop timeDamaged;
	bool drawDamaged;
	Point dRun[4];
	int indexRun;

	void update();
	void updateAnimation();
	void updateV();
	void updateBeforeHandle();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void restore(BaseObject* obj);
	void release();

	~Genjibo();
};

