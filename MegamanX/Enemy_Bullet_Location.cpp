#include "Enemy_Bullet_Location.h"


Enemy_Bullet_Location*Enemy_Bullet_Location::instance = 0;
Enemy_Bullet_Location * Enemy_Bullet_Location::getInstance()
{
	if (instance == 0)
		instance = new Enemy_Bullet_Location();
	return instance;
}

Enemy_Bullet_Location::Enemy_Bullet_Location()
{
	ptsCanon[0].init(44, 12);
	ptsCanon[1].init(43, 12);
	ptsCanon[2].init(41, 12);

	ptsBatton[0].init(7, 33);
	ptsBatton[1].init(10, 32);
	ptsBatton[2].init(12, 30);
	ptsBatton[3].init(11, 32);

}


Enemy_Bullet_Location::~Enemy_Bullet_Location()
{
}
