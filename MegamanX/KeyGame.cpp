#include "KeyGame.h"


KeyGame*KeyGame::instance = 0;

KeyGame * KeyGame::getInstance()
{
	if (instance == 0)
		instance = new KeyGame();
	return instance;
}

void KeyGame::update()
{
	keyLeft = key->IsKeyDown(DIK_LEFT);
	keyRight = key->IsKeyDown(DIK_RIGHT);
	keyJum = key->IsKeyDown(DIK_SPACE)|| key->IsKeyDown(DIK_X);
	keyAttack = key->IsKeyDown(DIK_C);
	keyMove = keyLeft || keyRight;
	keySlide = key->IsKeyDown(DIK_Z);
}
KeyGame::KeyGame()
{
	key = KEYBOARD;
	blockKeyLeft = false;
	blockKeyRight = false;
	blockKeyJump = false;
	blockKeySlide = false;
}


KeyGame::~KeyGame()
{
}
