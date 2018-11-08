#pragma once
#include"Enemy.h"

enum CANON_ACTION
{
	CA_RUN,
	CA_ATTACK
};
class Canon:public Enemy
{
public:
	GameTimeLoop timeBulletAppear;

	void update();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject* obj);

	Canon();
	~Canon();
};

