#pragma once
#include"DrawableObject.h"

class Door:public DrawableObject
{
public:
	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject* obj);
	Door();
	~Door();
};

