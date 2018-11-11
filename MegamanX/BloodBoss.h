#pragma once
#include"Blood.h"

class BloodBoss:public Blood
{
private:
	static BloodBoss* instance;
	BloodBoss();
public:
	static BloodBoss* getInstance();

	void update();
	void draw();
	void restore(BaseObject* obj);

	~BloodBoss();
};

