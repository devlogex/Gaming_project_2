#pragma once
#include"MovableObject.h"
#include"List.h"

class Weapon: public MovableObject
{
public:
	static List<Weapon*>*weapons;
	static List<Weapon*>*getWeapons();

	int damage;

	virtual void update();
	virtual void draw();
	virtual void updateLocation();

	virtual void onAABBCheck(BaseObject* other);

	Weapon();
	~Weapon();
};

