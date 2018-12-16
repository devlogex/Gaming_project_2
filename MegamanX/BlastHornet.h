#pragma once
#include"Enemy.h"
#include"Point.h"

enum BLASTHORNET_ACTION {
	BHA_APPEAR,
	BHA_PRICK,
	BHA_RETIRE,
	BHA_SHOT,
	BHA_RESHOT,
	BHA_FLY_HALF,
	BHA_FLY_FULL,
	BHA_SHOT_DIRECT,
	BHA_DEATH
};
class BlastHornet:public Enemy
{
private:
	static BlastHornet*instance;
	BlastHornet();

public:
	static BlastHornet*getInstance();

	GameTimeLoop timeAppear;
	GameTimeLoop timeShot;
	Point dRetire[3];
	int indexDRetire;

	Point ptsFly[2];
	int indexFlyFull;


	void update();
	void updateAnimation();
	void updateV();
	void updateBeforeHandle();
	void updateLocation();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void restore(BaseObject* obj);

	void fixV(float &vx, float &vy, float v);

	~BlastHornet();
};

