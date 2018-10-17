#pragma once
#include"MovableObject.h"

enum MEGAMAN_ACTION
{
	MA_APPEAR,
	MA_STAND,
	MA_JUMP,
	MA_RUN,
	MA_SLIDE,
	MA_WALL,
	MA_JUMPWALL,
	MA_HIGHJUMPWALL,
	MA_HIGHJUMP
};
class Megaman: public MovableObject
{
private:
	static Megaman*instance;
	Megaman();

public:
	static Megaman*getInstance();

	bool canJump;
	bool canSlide;
	bool canMoveLeft;
	bool canMoveRight;

	void update();
	void updateAnimation();
	void updateLocation();
	void draw();

	void onCollision(BaseObject * other, int nx, int ny);

	~Megaman();
};

