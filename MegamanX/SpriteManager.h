#pragma once
#include"Sprite.h"

enum SPRITE_OBJECT
{
	SPR_GROUND = -1,
	SPR_MAIN,
	SPR_WEAPON_SIMPLE,
	SPR_WEAPON_MEDIUM,
	SPR_WEAPON_LARGE,
	SPR_WEAPON_STATUS,
	SPR_CANON = 5,
	SPR_CANON_BULLET,
	SPR_BATTON = 7,
	SPR_BATTON_BULLET,
	SPR_DELETEOBJECT,
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