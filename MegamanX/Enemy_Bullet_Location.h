#pragma once
#include"Point.h"
class Enemy_Bullet_Location
{
private:
	static Enemy_Bullet_Location*instance;
	Enemy_Bullet_Location();

public:
	static Enemy_Bullet_Location*getInstance();

	Point ptsCanon[3];
	Point ptsBatton[4];
	Point ptsTrap[1];
	Point ptsBoss[1];
	Point ptsBlastHornet[1];
	~Enemy_Bullet_Location();
};

