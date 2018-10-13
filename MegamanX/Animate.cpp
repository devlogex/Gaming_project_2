#include "Animate.h"



void Animate::init(fstream & fs)
{
	int id;
	fs >> id >> nFrame;

	frames = new RectF[nFrame];
	for (int i = 0; i < nFrame; i++)
	{
		fs >> frames[i].x;
		fs >> frames[i].y;
		fs >> frames[i].width;
		fs >> frames[i].height;
	}
}


Animate::Animate()
{
}

Animate::~Animate()
{
	delete[]frames;
}
