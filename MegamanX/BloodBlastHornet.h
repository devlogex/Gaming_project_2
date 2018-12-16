#pragma once
#include"Blood.h"

class BloodBlastHornet:public Blood
{
private:
	static BloodBlastHornet* instance;
	BloodBlastHornet();
public:
	static BloodBlastHornet* getInstance();

	void update();
	void draw();
	void restore(BaseObject* obj);

	~BloodBlastHornet();
};

