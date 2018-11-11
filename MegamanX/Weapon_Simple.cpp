#include "Weapon_Simple.h"



Weapon_Simple::Weapon_Simple()
{
	sprite = SPRITEMANAGER->sprites[SPR_WEAPON_SIMPLE];
	damage = WEAPON_DAMAGE_SIMPLE;
}


Weapon_Simple::~Weapon_Simple()
{
}
