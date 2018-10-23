#pragma once
#include"DrawableObject.h"

enum WEAPON_STATUS
{
	WS_MEDIUM,
	WS_LARGE
};
class Weapon_Status:public DrawableObject
{
private:
	static Weapon_Status*instance;
	Weapon_Status();

public:
	static Weapon_Status*getInstance();
	bool allowDraw;
	void update();
	void draw();

	~Weapon_Status();
};

