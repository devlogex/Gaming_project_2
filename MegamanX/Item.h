#pragma once
#include"DrawableObject.h"

class Item:public DrawableObject
{
public:
	void draw();
	void update();
	void onAABBCheck(BaseObject* other);
	void onCollision(BaseObject* other, int nx, int ny);
	Item();
	~Item();
};

