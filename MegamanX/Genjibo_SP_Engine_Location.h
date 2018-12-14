#pragma once
#include"Point.h"

class Genjibo_SP_Engine_Location
{
private:
	static Genjibo_SP_Engine_Location*instance;
	Genjibo_SP_Engine_Location();

public:
	static Genjibo_SP_Engine_Location*getInstance();

	Point ptsFly[3][2];
	Point ptsShot[1][2];
	Point ptsAppear[1];

	~Genjibo_SP_Engine_Location();
};

