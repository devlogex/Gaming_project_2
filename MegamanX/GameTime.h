#pragma once
#include<Windows.h>
#include"Constant.h"

class GameTime
{
private:
	static GameTime*instance;

public:
	static GameTime* getInstance();

	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;
	float minFrameTime;
	float maxFrameTime;
	float frameTime;

	bool canCreateFrame();

	GameTime();
	~GameTime();
};

