#pragma once
#include"Point.h"

class BlastHornet_Wing_Location
{
private:
	static BlastHornet_Wing_Location*instance;
	BlastHornet_Wing_Location();

public:
	static 	BlastHornet_Wing_Location*getInstance();
	Point ptsAppear[28];
	Point ptsPrick[14];
	Point ptsRetire[8];
	Point ptsShot[6];
	Point ptsReShot[6];
	Point ptsFlyHalf[1];
	Point ptsFlyFull[1];
	Point ptsShotDirect[5];

	void release();
	~BlastHornet_Wing_Location();
};

