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
	sprites[SPR_WEAPON_STATUS] = new Sprite("Data\\Megaman\\weapon_status.png", "Data\\Megaman\\weapon_status.txt");
	sprites[SPR_CANON] = new Sprite("Data\\Enemy\\canon\\canon.png", "Data\\Enemy\\canon\\canon.txt");
	sprites[SPR_CANON_BULLET] = new Sprite("Data\\Enemy\\canon\\canon.png", "Data\\Enemy\\canon\\canon_bullet.txt");
	sprites[SPR_DELETEOBJECT] = new Sprite("Data\\Enemy\\deleteObject.png", "Data\\Enemy\\deleteObject.txt");
	sprites[SPR_BATTON]=new Sprite("Data\\Enemy\\batton\\batton.png", "Data\\Enemy\\batton\\batton.txt");
	sprites[SPR_BATTON_BULLET] = new Sprite("Data\\Enemy\\batton\\batton.png", "Data\\Enemy\\batton\\batton_bullet.txt");
	sprites[SPR_TRAP] = new Sprite("Data\\Enemy\\trap\\trap.png", "Data\\Enemy\\trap\\trap.txt");
	sprites[SPR_TRAP_BULLET] = new Sprite("Data\\Enemy\\trap\\trap.png", "Data\\Enemy\\trap\\trap_bullet.txt");
	sprites[SPR_BOSS]=new Sprite("Data\\Enemy\\boss\\boss.png", "Data\\Enemy\\boss\\boss.txt");
	sprites[SPR_BOSS_BULLET] = new Sprite("Data\\Enemy\\boss\\boss.png", "Data\\Enemy\\boss\\boss_bullet.txt");
	sprites[SPR_ITEM] = new Sprite("Data\\Item\\item.png", "Data\\Item\\item.txt");
	sprites[SPR_BLOOD_MEGAMAN] = new Sprite("Data\\Blood\\blood_megaman.png", "Data\\Blood\\blood_megaman.txt");
	sprites[SPR_BLOOD_BOSS] = new Sprite("Data\\Blood\\blood_boss.png", "Data\\Blood\\blood_boss.txt");
	sprites[SPR_DOOR] = new Sprite("Data\\Door\\door.png", "Data\\Door\\door.txt");
	sprites[SPR_GENJIBO] = new Sprite("Data\\Enemy\\genjibo\\genjibo.png", "Data\\Enemy\\genjibo\\genjibo.txt");
	sprites[SPR_GENJIBO_SP] = new Sprite("Data\\Enemy\\genjibo\\genjibo_sp\\genjibo_sp.png", "Data\\Enemy\\genjibo\\genjibo_sp\\genjibo_sp.txt");
	sprites[SPR_GENJIBO_SP_ENGINE] = new Sprite("Data\\Enemy\\genjibo\\genjibo_sp\\genjibo_sp.png", "Data\\Enemy\\genjibo\\genjibo_sp\\genjibo_sp_engine.txt");
	sprites[SPR_BLASTHORNET] = new Sprite("Data\\Enemy\\blastHornet\\blastHornet.png", "Data\\Enemy\\blastHornet\\blastHornet.txt");
	sprites[SPR_BLOOD_BLASTHORNET]=new Sprite("Data\\Blood\\blood_BlastHornet.png", "Data\\Blood\\blood_BlastHornet.txt");
	sprites[SPR_BLASTHORNET_BULLET]=new Sprite("Data\\Enemy\\blastHornet\\blastHornet.png", "Data\\Enemy\\blastHornet\\blastHornet_bullet.txt");
	sprites[SPR_BLASTHORNET_WING]=new Sprite("Data\\Enemy\\blastHornet\\blastHornet.png", "Data\\Enemy\\blastHornet\\blastHornet_wing.txt");
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