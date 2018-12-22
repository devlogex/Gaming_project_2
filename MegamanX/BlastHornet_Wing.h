#pragma once
#include"DrawableObject.h"

class BlastHornet_Wing:public DrawableObject
{
private:
	static BlastHornet_Wing*instance;
	BlastHornet_Wing();

public:
	static BlastHornet_Wing*getInstance();

	void update();
	void draw();
	void restore(BaseObject* obj);
	void release();
	~BlastHornet_Wing();
};

