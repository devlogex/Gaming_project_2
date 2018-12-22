#include "BlastHornet_Wing_Location.h"


BlastHornet_Wing_Location * BlastHornet_Wing_Location::instance = 0;
BlastHornet_Wing_Location * BlastHornet_Wing_Location::getInstance()
{
	if (instance == 0)
		instance = new BlastHornet_Wing_Location();
	return instance;
}

BlastHornet_Wing_Location::BlastHornet_Wing_Location()
{
	ptsAppear[0].x = 25;
	ptsAppear[0].y = 14;
	ptsAppear[1].x = 19;
	ptsAppear[1].y = 14;
	ptsAppear[2].x = 14;
	ptsAppear[2].y = 14;
	ptsAppear[3].x = 14;
	ptsAppear[3].y = 17;


}

void BlastHornet_Wing_Location::release()
{
	delete instance;
	instance = 0;
}

BlastHornet_Wing_Location::~BlastHornet_Wing_Location()
{
}
