#include <Windows.h>
#include <string>
#include "WindowGame.h"
#include "Graphics.h"
#include "Texture.h"
#include "KeyGame.h"
#include "GameTime.h"
#include "Megaman.h"
#include "MegamanXScene.h"
#include "MainScreen.h"
#include "GameSound.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WINDOW->initHandleWindows(hInstance, nCmdShow);

	MegamanXScene::changeScene(new MainScreen());

	KeyBoard::Create(hInstance, WINDOW->getHandleWindow());

	GAME_TIME->minFrameTime = MIN_FRAME_TIME;
	GAME_TIME->maxFrameTime = MAX_FRAME_TIME;
	
	GameSound::initialize(WINDOW->getHandleWindow());

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (GAME_TIME->canCreateFrame())
			{
				KEYBOARD->PollKeyboard();
				KEYBOARD->updateKeyBoard();
				KEY->update();

				CURSCENE->update();

				GRAPHICS->BeginGraphics();
				
				CURSCENE->draw();

				GRAPHICS->EndGraphics();
				GRAPHICS->PresentBackBuffer();
			}
			else
			{
				timeBeginPeriod(1);
				Sleep((DWORD)(1000 * (GAME_TIME->minFrameTime)));
				timeEndPeriod(1);
			}
		}
	}

	delete WINDOW;
	delete GRAPHICS;

	if (MegamanXScene::curScene != 0)
		delete MegamanXScene::curScene;

	return nCmdShow;
}
