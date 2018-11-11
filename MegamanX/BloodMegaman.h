#pragma once
#include"Blood.h"

class BloodMegaman:public Blood
{
private:
	static BloodMegaman* instance;
	BloodMegaman();

public:
	static BloodMegaman* getInstance();
	
	void update();
	void draw();
	void restore(BaseObject* obj);

	~BloodMegaman();
};

