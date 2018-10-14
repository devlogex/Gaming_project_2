#pragma once
#include"MovableObject.h"

enum MEGAMAN_ACTION
{
	MA_APPEAR,
	MA_STAND,
	MA_JUMP,
	MA_RUN,
	MA_SLIDE,
	MA_CLIMB,
	MA_NEARDEATH,
	MA_DIE,
	MA_DISAPPEAR
};
class Megaman: public MovableObject
{
private:
	static Megaman*instance;
	Megaman();

public:
	static Megaman*getInstance();

	void update();
	void updateAnimation();
	void updateLocation();
	void draw();

	void onCollision(BaseObject * other, int nx, int ny);

	~Megaman();
};

