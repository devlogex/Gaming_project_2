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

}


Enemy_Bullet_Location::~Enemy_Bullet_Location()
{
}
