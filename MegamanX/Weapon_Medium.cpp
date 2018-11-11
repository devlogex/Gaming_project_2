#include "Weapon_Medium.h"



Weapon_Medium::Weapon_Medium()
{
	sprite = SPRITEMANAGER->sprites[SPR_WEAPON_MEDIUM];
	damage = WEAPON_DAMAGE_MEDIUM;
}


Weapon_Medium::~Weapon_Medium()
{
}
