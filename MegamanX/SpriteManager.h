#pragma once
#include"Sprite.h"

enum SPRITE_OBJECT
{
	SPR_GROUND = -1,
	SPR_MAIN,
	SPR_CANON = 1,
	SPR_BATTON = 2,
	SPR_TRAP = 3,
	SPR_BOSS = 4,
	SPR_ITEM = 5,
	SPR_DOOR = 6,
	SPR_BOSS_BULLET,
	SPR_WEAPON_SIMPLE,
	SPR_WEAPON_MEDIUM,
	SPR_WEAPON_LARGE,
	SPR_WEAPON_STATUS,
	SPR_CANON_BULLET,
	SPR_BATTON_BULLET,
	SPR_TRAP_BULLET,
	SPR_DELETEOBJECT,
	SPR_BLOOD_MEGAMAN,
	SPR_BLOOD_BOSS,
	SPR_COUNT
};

class SpriteManager
{
private:
	static SpriteManager*instance;

	SpriteManager();
public:
	static SpriteManager*getInstance();

	Sprite** sprites;

	~SpriteManager();
};