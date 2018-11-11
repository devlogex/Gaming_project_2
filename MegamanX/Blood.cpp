#include "Blood.h"
#include"BloodBoss.h"
#include"BloodMegaman.h"
#include"Megaman.h"

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
	if (MEGAMAN->x > 4370 && !bloods->_Contain(BLOOD_BOSS))
		bloods->_Add(BLOOD_BOSS);
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
