#pragma once
#define CLASS_NAME "MegamanX"
#define TITLE_STR "MegamanX"

#define PI 3.14159265358979323846f
#define ANIMATE_DELAY_TIME_DEFAULT	0.08f
#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		600
#define VIEWPORT_WIDTH		243
#define VIEWPORT_HEIGHT		230
#define BACK_WIDTH			VIEWPORT_WIDTH
#define BACK_HEIGHT			VIEWPORT_HEIGHT
#define GRAVITY				550
#define X_MAP				13
#define Y_MAP				529
#define MEGAMAN_VX_RUN		50
#define MEGAMAN_VX_SLIDE	150
#define MEGAMAN_VY_JUMP		-250
#define MEGAMAN_VY_WALL_DOWN	10
#define MEGAMAN_VY_WALL_UP	-200
#define MEGAMAN_VY_WALL_UP_H -250
#define MEGAMAN_VX_WALL		90
#define MEGAMAN_VX_WALL_H	110
#define MEGAMAN_AX			500
#define WEAPON_VX			250
#define ENEMY_VX_GO			60
#define ENEMY_BULLET_VX		100
#define BOSS_VX				150
#define MEGAMAN_LIFE		150
#define BOSS_LIFE			1
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
#define GENJIBO_SP_VY		100
#define GENJIBO_VX			100
#define GENJIBO_VY			-300
#define GENJIBO_DX			1.2
#define GENJIBO_DY			1.2
#define GENJIBO_LIFE		1
#define GENJIBO_DAMAGE		20
#define BLASTHORNET_LIFE	1
#define BLASTHORNET_DAMAGE	25
#define BLASTHORNET_FLY_VX	70
#define BLASTHORNET_FLY_VY	170
#define BLASTHORNET_BULLET_DAMAGE	20

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
#define BLOOD_BLASTHORNET	BloodBlastHornet::getInstance()
#define BOSS				Boss::getInstance()
#define GENJIBO_SP			Genjibo_SP::getInstance()
#define GENJIBO_SP_ENGINE	Genjibo_SP_Engine::getInstance()
#define GENJIBO				Genjibo::getInstance()
#define GENJIBO_SP_ENGINE_LOCATION Genjibo_SP_Engine_Location::getInstance()
#define BLASTHORNET			BlastHornet::getInstance()
#define BLASTHORNET_WING	BlastHornet_Wing::getInstance()
#define GAMESOUND			GameSound::getInstance()

#define AUDIO_FORMAT_TAG		WAVE_FORMAT_PCM
#define	AUDIO_NUM_OF_CHANNEL	2
#define AUDIO_SAMPLE_SPEED		22050
#define AUDIO_BITS_PER_SAMPLE	16
#define AUDIO_FLAGS				0
#define AUDIO_BUFFER_SIZE		640000
#define AUDIO_GUID				GUID_NULL
#define AUDIO_BLOCK_ALIGN(bitPerSample, nChannels)		(WORD)(bitPerSample / 8 * nChannels)
#define AUDIO_AVERAGE_BPS(samplesPerSec, blockAlign)	(DWORD)(samplesPerSec * blockAlign)

#define AUDIO_FIRST_STAGE	"Data\\Sound\\First_Stage.wav"		///
#define AUDIO_JUMP			"Data\\Sound\\Jump.wav"				///
#define AUDIO_SHOT			"Data\\Sound\\Shot.wav"				///
#define AUDIO_CHARGE		"Data\\Sound\\Charge.wav"			///
#define AUDIO_BLASTHORNET_STAGE	"Data\\Sound\\BlastHornet.wav"	///
#define AUDIO_BOSS_DIE		"Data\\Sound\\Boss_die.wav"
#define AUDIO_CREP_DIE		"Data\\Sound\\Crep_die.wav"
#define AUDIO_ITEM			"Data\\Sound\\Pick_up_item.wav"		///
#define	AUDIO_SLIDE			"Data\\Sound\\Slide.wav"			///

#define FRAME_RATE			(80.0f)  // Số frame load trên một giây (frame/giây)
#define MIN_FRAME_RATE		(60.0f)
#define MIN_FRAME_TIME		(1.0f/FRAME_RATE)	// thời gian load một frame (giây/frame)
#define MAX_FRAME_TIME		(1.0f/MIN_FRAME_TIME)