#pragma once

enum GAMESTATE
{
	START,
	RUN,
	PAUSE,
	PAUSE_ENEMY,
	STOP
};

class GameState
{
public:
	static GAMESTATE curState;

	GameState();
	~GameState();
};

