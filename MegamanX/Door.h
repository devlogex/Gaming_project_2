#pragma once
#include"DrawableObject.h"
#include"List.h"
class Door:public DrawableObject
{
public:
	static List<Door*>*doors;
	bool opening;
	bool isOpened;

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void restore(BaseObject* obj);
	Door();
	~Door();
};