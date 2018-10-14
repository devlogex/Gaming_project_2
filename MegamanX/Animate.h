#pragma once
#include"RectF.h"
#include<fstream>
using namespace std;


class Animate
{
public:
	RectF* frames;
	int nFrame;

	void init(fstream &fs);
	Animate();
	~Animate();
};