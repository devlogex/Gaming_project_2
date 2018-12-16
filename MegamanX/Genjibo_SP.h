#pragma once
#include"Enemy.h"

enum GENJIBO_SP_ACTION {
	GSA_FLY,
	GSA_SHOT
};
class Genjibo_SP:public Enemy
{
private:
	static Genjibo_SP*instance;
	Genjibo_SP();
public:
	static Genjibo_SP*getInstance();
	bool isActive;
	GameTimeLoop timeShot;

	void update();
	void updateAnimation();
	void updateVY();
	void updateBeforeHandle();
	void updateLocation();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void restore(BaseObject* obj);
	void release();
	~Genjibo_SP();
};

