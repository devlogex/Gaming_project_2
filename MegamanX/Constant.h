#pragma once
#define CLASS_NAME "MegamanX"
#define TITLE_STR "MegamanX"

#define ANIMATE_DELAY_TIME_DEFAULT	0.05f
#define SCREEN_WIDTH		557
#define SCREEN_HEIGHT		700
#define VIEWPORT_WIDTH		230
#define VIEWPORT_HEIGHT		289
#define BACK_WIDTH			VIEWPORT_WIDTH
#define BACK_HEIGHT			VIEWPORT_HEIGHT
#define GRAVITY				550
#define X_MAP				17
#define Y_MAP				476
#define MEGAMAN_VX_RUN		80
#define MEGAMAN_VX_SLIDE	160
#define MEGAMAN_VY_JUMP		-300

#define WINDOW				WindowGame::getInstance()
#define GRAPHICS			Graphics::getInstance()
#define GAME_TIME			GameTime::getInstance()
#define SPRITEMANAGER		SpriteManager::getInstance()
#define KEYBOARD			KeyBoard::getInstance()
#define KEY					KeyGame::getInstance()
#define COLLISION			CollisionManager::getInstance()
#define CAMERA				Camera::getInstance()
#define CURSCENE			MegamanXScene::curScene
#define MEGAMAN				Megaman::getInstance()

#define FRAME_RATE			(20.0f)  // Số frame load trên một giây (frame/giây)
#define MIN_FRAME_RATE		(10.0f)
#define MIN_FRAME_TIME		(1.0f/FRAME_RATE)	// thời gian load một frame (giây/frame)
#define MAX_FRAME_TIME		(1.0f/MIN_FRAME_TIME)