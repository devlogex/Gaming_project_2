#include "Blood.h"
#include"BloodBoss.h"
#include"BloodMegaman.h"
#include"Megaman.h"
#include"Stage.h"
#include"BloodBlastHornet.h"

List<Blood*>* Blood::bloods = 0;
List<Blood*>* Blood::getBloods()
{
	if (bloods == 0)
	{
		bloods = new List<Blood*>();
		bloods->_Add(BLOOD_MEGAMAN);
	}
	return bloods;
}

void Blood::update()
{
	if (Stage::curStage->index == 7 && !bloods->_Contain(BLOOD_BOSS))
		bloods->_Add(BLOOD_BOSS);
	if (Stage::curStage->index == 4 && !bloods->_Contain(BLOOD_BLASTHORNET))
		bloods->_Add(BLOOD_BLASTHORNET);
}

void Blood::draw()
{
}

void Blood::restore(BaseObject * obj)
{
}

Blood::Blood()
{
}


Blood::~Blood()
{
}
