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
	MA_HIGHJUMP,
	MA_STAND_ATTACK,
	MA_JUMP_ATTACK,
	MA_RUN_ATTACK,
	MA_SLIDE_ATTACK,
	MA_WALL_ATTACK,
	MA_JUMPWALL_ATTACK,
	MA_HIGHJUMPWALL_ATTACK,
	MA_HIGHJUMP_ATTACK,
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
	bool holdingAttack;
	GameTimeLoop timeAttack;
	GameTimeLoop timeWeaponAppear;

	void toAttack();
	void toNormal();
	void statusNormal();
	void statusAttack();
	void updateVX();
	void updateBlock();
	void updateBeforeHandle();

	void update();
	void updateAnimation();
	void updateLocation();
	void draw();

	int updateY;

	void onCollision(BaseObject * other, int nx, int ny);

	~Megaman();
};

