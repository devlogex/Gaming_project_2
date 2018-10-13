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