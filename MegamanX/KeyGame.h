#pragma once
#include"KeyBoard.h"
#include"Constant.h"


class KeyGame
{
private:
	KeyBoard* key;

	static KeyGame*instance;
	KeyGame();

public:
	static KeyGame*getInstance();

	bool keyLeft;
	bool keyRight;
	bool keyJum;
	bool keyAttack;
	bool keySlide;
	bool keyMove;


	bool keyUp;
	bool keyUpPress;
	bool isKeyUpDownPrevious;

	bool keyDown;
	bool keyDownPress;
	bool isKeyDownDownPrevious;

	bool keyEnter;
	bool keyEnterPress;
	bool isKeyEnterDownPrevious;

	void update();

	~KeyGame();
};

