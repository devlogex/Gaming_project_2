#include "WeaponLocation.h"


WeaponLocation*WeaponLocation::instance = 0;
WeaponLocation * WeaponLocation::getInstance()
{
	if (instance == 0)
		instance = new WeaponLocation();
	return instance;
}


WeaponLocation::WeaponLocation()
{
	ptsStand[0].init(29, 16);
	ptsStand[1].init(28, 16);

	ptsJump[0].init(28, 14);
	ptsJump[1].init(23, 13);
	ptsJump[2].init(25, 15);
	ptsJump[3].init(29, 13);
	ptsJump[4].init(30, 13);

	ptsRun[0].init(28, 14);
	ptsRun[1].init(31, 14);
	ptsRun[2].init(34, 14);
	ptsRun[3].init(37, 14);
	ptsRun[4].init(33, 14);
	ptsRun[5].init(30, 14);
	ptsRun[6].init(32, 14);
	ptsRun[7].init(34, 14);
	ptsRun[8].init(36, 14);
	ptsRun[9].init(34, 14);

	ptsSlide[0].init(37, 13);
	ptsSlide[1].init(48, 12);
	ptsSlide[2].init(48, 12);
	ptsSlide[3].init(48, 12);
	ptsSlide[4].init(48, 12);
	ptsSlide[5].init(48, 12);

	ptsWall[0].init(2, 21);

	ptsJumpWall[0].init(30, 12);
	ptsJumpWall[1].init(30, 12);
	ptsJumpWall[2].init(31, 12);

	ptsHighJumpWall[0].init(30, 12);
	ptsHighJumpWall[1].init(30, 12);
	ptsHighJumpWall[2].init(31, 12);

	ptsHighJump[0].init(28, 14);
	ptsHighJump[1].init(23, 13);
	ptsHighJump[2].init(25, 15);
	ptsHighJump[3].init(29, 13);
	ptsHighJump[4].init(30, 13);
}

WeaponLocation::~WeaponLocation()
{
}
