#pragma once
#define CLASS_NAME "MegamanX"
#define TITLE_STR "MegamanX"

#define ANIMATE_DELAY_TIME_DEFAULT	0.08f
#define SCREEN_WIDTH		600
#define SCREEN_HEIGHT		600
#define VIEWPORT_WIDTH		150
#define VIEWPORT_HEIGHT		150
#define BACK_WIDTH			VIEWPORT_WIDTH
#define BACK_HEIGHT			VIEWPORT_HEIGHT
#define GRAVITY				550
#define X_MAP				59
#define Y_MAP				585
#define MEGAMAN_VX_RUN		60
#define MEGAMAN_VX_SLIDE	150
#define MEGAMAN_VY_JUMP		-230
#define MEGAMAN_VY_WALL_DOWN	10
#define MEGAMAN_VY_WALL_UP	-200
#define MEGAMAN_VY_WALL_UP_H -250
#define MEGAMAN_VX_WALL		90
#define MEGAMAN_VX_WALL_H	110
#define MEGAMAN_AX			500
#define WEAPON_VX			210
#define ENEMY_VX_GO			60
#define ENEMY_BULLET_VX		100
#define BOSS_VX				150
#define MEGAMAN_LIFE		100
#define BOSS_LIFE			500
#define TRAP_LIFE			20
#define BATTON_LIFE			20
#define	CANON_LIFE			35
#define ENEMY_DAMAGE		10
#define BOSS_DAMAGE			20
#define CANON_BL_DAMAGE		5
#define TRAP_BL_DAMAGE		15
#define BATTON_BL_DAMAGE	20
#define	BOSS_BL_DAMAGE		10
#define WEAPON_DAMAGE_SIMPLE	5
#define	WEAPON_DAMAGE_MEDIUM	10
#define WEAPON_DAMAGE_LARGE		40


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
#define WEAPONLOCATION		WeaponLocation::getInstance()
#define WEAPON				Weapon::getWeapons()
#define WEAPONSTATUS		Weapon_Status::getInstance()
#define ENEMYBULLETLOCATION	Enemy_Bullet_Location::getInstance()
#define ENEMYBULLET			Enemy_Bullet::getEnemyBullets()
#define BLOOD				Blood::getBloods()
#define BLOOD_MEGAMAN		BloodMegaman::getInstance()
#define BLOOD_BOSS			BloodBoss::getInstance()
#define BOSS				Boss::getInstance()

#define FRAME_RATE			(100.0f)  // Số frame load trên một giây (frame/giây)
#define MIN_FRAME_RATE		(90.0f)
#define MIN_FRAME_TIME		(1.0f/FRAME_RATE)	// thời gian load một frame (giây/frame)
#define MAX_FRAME_TIME		(1.0f/MIN_FRAME_TIME)