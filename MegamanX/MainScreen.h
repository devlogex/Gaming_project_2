#pragma once
#include"Scene.h"
#include"Sprite.h"
#include"DrawableObject.h"

enum BUTTON {
	BUTTON_START,
	BUTTON_CONTINUE
};
class MainScreen:public Scene
{
public:
	Texture*	background;
	DrawableObject* button;

	bool isStart;
	bool isDraw;
	GameTimeLoop timeDraw;
	void init();
	void update();
	void draw();

	MainScreen();
	~MainScreen();
};

