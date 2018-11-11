#pragma once
#include"DrawableObject.h"
#include"List.h"

class Blood:public DrawableObject
{
public:
	static List<Blood*>*bloods;
	static List<Blood*>*getBloods();

	virtual void update();
	virtual void draw();
	virtual void restore(BaseObject* obj);
	Blood();
	~Blood();
};

