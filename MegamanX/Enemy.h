#pragma once
#include"MovableObject.h"
#include"GameTimeLoop.h"


class Enemy:public MovableObject
{
public:
	int damage;
	GameTimeLoop timeDeath;
	virtual void update();
	virtual void updateLocation();
	virtual void draw();
	virtual void onCollision(BaseObject* other, int nx, int ny);
	virtual void onAABBCheck(BaseObject* other);
	virtual void restore(BaseObject* obj);

	Enemy();
	~Enemy();
};

