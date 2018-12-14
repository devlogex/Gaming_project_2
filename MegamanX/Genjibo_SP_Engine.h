#pragma once
#include"DrawableObject.h"

enum Genjibo_SP_Engine_ACTION {
	GSEA_FLY,
	GSEA_SHOT,
	GSEA_APPEAR
};
class Genjibo_SP_Engine:public DrawableObject
{
private:
	static Genjibo_SP_Engine*instance;
	Genjibo_SP_Engine();

public:
	static Genjibo_SP_Engine*getInstance();

	void update();
	void draw();
	void restore(BaseObject* obj);
	void release();
	~Genjibo_SP_Engine();
};

