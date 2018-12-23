#pragma once
#include"Constant.h"



#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")

#include <sstream>
#include <iostream>
#include <dsound.h>
#include<vector>
#include "CWaveFile.h"

enum SOUND_ID
{
	ID_SOUND_MAP1,
	ID_SOUND_JUMP,
	ID_SOUND_COIN,
	ID_TAIL_TALLWHIP,
	ID_SOUND_MUSHROOM_OBTAIN,
	ID_SOUND_RACOON_LEFT_OBTAIN,
	ID_SOUND_LIFE_UP,
	ID_SOUND_MARIO_SLIPING,
	ID_SOUND_BEAN_STALK,
	ID_SOUND_PIPE_MAZE,
	ID_SOUND_SQUISH,
	ID_SOUND_MARIO_ATTACK,
	ID_SOUND_BLOCK_BREAKING
};
// -----------------------------------------------
// Name: class TSound
// Desc: used to load/ store/ play an audio with wav extension.
// -----------------------------------------------
class Sound
{
public:
	Sound(const char* audioPath);
	~Sound(void);

	static HRESULT initializeSoundClass(HWND windowsHandler);
	static HRESULT releaseSoundClass();

	HRESULT play(bool isLoop = false, DWORD priority = 0);
	HRESULT stop();


private:
	HRESULT loadAudio(const char* audioPath);

private:
	static WAVEFORMATEX bufferFormat_;
	static DSBUFFERDESC bufferDescription_;
	static LPDIRECTSOUND8 audioHandler_;
	static HWND windowsHandler_;

	LPDIRECTSOUNDBUFFER soundBuffer_;
};
