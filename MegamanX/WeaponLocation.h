#pragma once
#include"Point.h"

class WeaponLocation
{
private:
	static WeaponLocation*instance;
	WeaponLocation();

public:
	static WeaponLocation*getInstance();

	Point ptsStand[2];
	Point ptsJump[5];
	Point ptsRun[10];
	Point ptsSlide[6];
	Point ptsWall[1];
	Point ptsJumpWall[3];
	Point ptsHighJumpWall[3];
	Point ptsHighJump[5];

	~WeaponLocation();
};

