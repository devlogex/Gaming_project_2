#include "Genjibo_SP_Engine_Location.h"


Genjibo_SP_Engine_Location*Genjibo_SP_Engine_Location::instance = 0;
Genjibo_SP_Engine_Location * Genjibo_SP_Engine_Location::getInstance()
{
	if (instance == 0)
		instance = new Genjibo_SP_Engine_Location();
	return instance;
}

Genjibo_SP_Engine_Location::Genjibo_SP_Engine_Location()
{
	ptsFly[0][0].init(2, 13);
	ptsFly[0][1].init(16, 13);
	ptsFly[1][0].init(2, 13);
	ptsFly[1][1].init(16, 13);
	ptsFly[2][0].init(-2, 13);
	ptsFly[2][1].init(16, 13);

	ptsShot[0][0].init(2, 13);
	ptsShot[0][1].init(16, 13);

	ptsAppear[0].init(-4, 21);
}


Genjibo_SP_Engine_Location::~Genjibo_SP_Engine_Location()
{
}
