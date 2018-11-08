#include "SpriteManager.h"


SpriteManager*SpriteManager::instance = 0;
SpriteManager * SpriteManager::getInstance()
{
	if (instance == 0)
		instance = new SpriteManager();
	return instance;
}

SpriteManager::SpriteManager()
{
	sprites = new Sprite*[SPR_COUNT];
	sprites[SPR_MAIN] = new Sprite("Data\\Megaman\\megaman.png", "Data\\Megaman\\megaman.txt");
	sprites[SPR_WEAPON_SIMPLE] = new Sprite("Data\\Megaman\\weapon.png", "Data\\Megaman\\weapon_simple.txt");
	sprites[SPR_WEAPON_MEDIUM] = new Sprite("Data\\Megaman\\weapon.png", "Data\\Megaman\\weapon_medium.txt");
	sprites[SPR_WEAPON_LARGE] = new Sprite("Data\\Megaman\\weapon.png", "Data\\Megaman\\weapon_large.txt");
	sprites[SPR_WEAPON_STATUS] = new Sprite("Data\\Megaman\\weapon.png", "Data\\Megaman\\weapon_status.txt");
	sprites[SPR_CANON] = new Sprite("Data\\Enemy\\canon\\canon.png", "Data\\Enemy\\canon\\canon.txt");
	sprites[SPR_CANON_BULLET] = new Sprite("Data\\Enemy\\canon\\canon.png", "Data\\Enemy\\canon\\canon_bullet.txt");
	sprites[SPR_DELETEOBJECT] = new Sprite("Data\\Enemy\\deleteObject.png", "Data\\Enemy\\deleteObject.txt");
	sprites[SPR_BATTON]=new Sprite("Data\\Enemy\\batton\\batton.png", "Data\\Enemy\\batton\\batton.txt");
	sprites[SPR_BATTON_BULLET] = new Sprite("Data\\Enemy\\batton\\batton.png", "Data\\Enemy\\batton\\batton_bullet.txt");

}

SpriteManager::~SpriteManager()
{
	for (int i = 0; i < SPR_COUNT; i++)
	{
		delete sprites[i]->image;
		delete[] sprites[i]->animates;
		delete sprites[i];
	}
}