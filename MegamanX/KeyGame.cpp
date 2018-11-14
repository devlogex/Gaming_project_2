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


	keyUp = key->IsKeyDown(DIK_UP);
	keyUpPress = keyUp && !isKeyUpDownPrevious;
	isKeyUpDownPrevious = keyUp;

	keyDown = key->IsKeyDown(DIK_DOWN);
	keyDownPress = keyDown && !isKeyDownDownPrevious;
	isKeyDownDownPrevious = keyDown;

	keyEnter=key->IsKeyDown(DIK_RETURN);
	keyEnterPress = keyEnter && !isKeyEnterDownPrevious;
	isKeyEnterDownPrevious = keyEnter;
}
KeyGame::KeyGame()
{
	key = KEYBOARD;

	isKeyEnterDownPrevious = false;
	isKeyDownDownPrevious = false;
	isKeyUpDownPrevious = false;
}


KeyGame::~KeyGame()
{
}
