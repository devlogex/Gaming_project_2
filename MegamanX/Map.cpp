#include "Map.h"
#include"DrawableObject.h"
#include"Camera.h"
#include"Megaman.h"
#include"Weapon.h"
#include"Weapon_Status.h"
#include"Canon.h"
#include"Enemy_Bullet.h"
#include"Batton.h"
#include"Batton_Bullet.h"
#include"Trap.h"
#include"Boss.h"
#include"Item.h"
#include"Blood.h"
#include"BloodMegaman.h"
#include"BloodBoss.h"
#include"Door.h"
#include"Genjibo_SP.h"
#include"Genjibo.h"
#include"BlastHornet.h"

Map* Map::curMap = 0;
Map::Map()
{
	Map::curMap = this;
	xMap = X_MAP;
	yMap = Y_MAP;
	viewportWidth = VIEWPORT_WIDTH;
	viewportHeight = VIEWPORT_HEIGHT;
	CAMERA->x = xMap;
	CAMERA->y = yMap;
	CAMERA->width = viewportWidth;
	CAMERA->height = viewportHeight;
}


Map::~Map()
{
}

void Map::convertToViewportPos(int xInMap, int yInMap, int & xViewport, int & yViewport)
{
	D3DXVECTOR3 posInMap;
	D3DXVECTOR4 posViewport;
	D3DXMATRIX mt;

	D3DXMatrixIdentity(&mt);
	mt._41 = -(int)xMap;
	mt._42 = -(int)yMap;

	posInMap.x = xInMap;
	posInMap.y = yInMap;
	posInMap.z = 0;

	D3DXVec3Transform(&posViewport, &posInMap, &mt);
	xViewport = posViewport.x;
	yViewport = posViewport.y;
}

void Map::render()
{

}

void Map::initObjects(const char * objectsPath)
{
	fstream fs(objectsPath);
	fs >> nObjects;
	int id;
	float x, y, width, height;

	objects = new BaseObject*[nObjects];

	for (int i = 0; i < nObjects; i++)
	{
		fs >> id >> x >> y >> width >> height;

		switch (id%10)
		{
		case SPR_CANON:
			objects[i] = new Canon();
			break;
		case SPR_BATTON:
			objects[i] = new Batton();
			break;
		case SPR_TRAP:
			objects[i] = new Trap();
			break;
		case SPR_BOSS:
			objects[i] = BOSS;
			break;
		case SPR_ITEM:
			objects[i] = new Item();
			break;
		case SPR_DOOR:
			objects[i] = new Door();
			break;
		case SPR_GENJIBO_SP:
			objects[i] = GENJIBO_SP;
			break;
		case SPR_GENJIBO:
			objects[i] = GENJIBO;
			break;
		case SPR_BLASTHORNET:
			objects[i] = BLASTHORNET;
			break;
		default:
			objects[i] = new BaseObject();
			break;
		}

		objects[i]->id = id;
		objects[i]->x = x;
		objects[i]->y = y;
		objects[i]->width = width;
		objects[i]->height = height;

		if (id >= 0)
		{
			DrawableObject* drawableObject = (DrawableObject*)objects[i];
			drawableObject->setSprite();

			// Direction for Trap
			if (id % 10 == 3)
				if (id > 100)
					drawableObject->direction = Left;
				else
					drawableObject->direction = Right;
		}
		else
		{
			if (id == -2)
				objects[i]->collisionType = CT_PREVENTMOVECAMERA;
			else
				if (id == -3)
					objects[i]->collisionType = CT_TRAP;
		}

		objects[i]->getFromObject(objects[i]);
		
	}

	fs.close();
}

void Map::init(const char * mapSheetPath, const char * objectsPath, const char * quadtreePath)
{
	mapSheetImg.Init(mapSheetPath, D3DCOLOR_XRGB(0, 0, 0));
	initObjects(objectsPath);
	quadtree.init(quadtreePath, objects);
}

void Map::initStage(const char * stageInfoPath)
{
	fstream fs(stageInfoPath);
	int nStage;
	fs >> nStage;

	for (int i = 0; i < nStage; i++)
		stages._Add(new Stage(fs, i));

	Stage::curStages = &stages;
	if (Stage::curStage == 0)
		Stage::curStage = stages[4];
}

void Map::restoreAllObject()
{
	for (int i = 0; i < nObjects; i++)
		if (objects[i]->id > 0)
		{
			DrawableObject* drawableObject = (DrawableObject*)objects[i];
			drawableObject->restore(objects[i]);
		}
}

void Map::update()
{
	Stage::curStage->update();
	CAMERA->update();
	quadtree.update();
	MEGAMAN->update();
	WEAPONSTATUS->update();

	for (int i = 0; i < WEAPON->size(); i++)
	{
		WEAPON->at(i)->update();
	}

	for (int i = 0; i < ENEMYBULLET->size(); i++)///////////////////////
	{
		ENEMYBULLET->at(i)->update();
	}

	List<BaseObject*> groundsObject = CAMERA->objectsInCamera.grounds;
	List<Enemy*> enemiesObject = CAMERA->objectsInCamera.enemies;/////////
	List<BaseObject*>preventMoveCamera = CAMERA->objectsInCamera.preventMoveCameras;
	List<Item*>itemObject = CAMERA->objectsInCamera.items;
	List<BaseObject*>trapObject = CAMERA->objectsInCamera.traps;
	List<Door*>doorObject = CAMERA->objectsInCamera.doors;

	for (int i = 0; i < doorObject.size(); i++)
		doorObject[i]->update();

	for (int i = 0; i < trapObject.size(); i++)
		COLLISION->checkCollision(trapObject[i], MEGAMAN);
	for (int i = 0; i < itemObject.size(); i++)
		COLLISION->checkCollision(MEGAMAN, itemObject[i]);

	for (int j = 0; j < enemiesObject.size(); j++)/////////
	{
		enemiesObject[j]->update();
	}
	for (int i = 0; i < ENEMYBULLET->size(); i++)
		ENEMYBULLET->at(i)->update();

	for (int i = 0; i < groundsObject.size(); i++)
	{
		COLLISION->checkCollision(MEGAMAN, groundsObject[i]);

		for (int j = 0; j < enemiesObject.size(); j++)//////////////////
			COLLISION->checkCollision(enemiesObject[j], groundsObject[i]);
		for (int j = 0; j < ENEMYBULLET->size(); j++)
			COLLISION->checkCollision(ENEMYBULLET->at(j), groundsObject[i]);
	}

	for (int i = 0; i < ENEMYBULLET->size(); i++)///////////////////////
	{
		COLLISION->checkCollision(MEGAMAN, ENEMYBULLET->at(i));
	}

	for (int j = 0; j < enemiesObject.size(); j++)//////////////////
	{
		COLLISION->checkCollision(MEGAMAN,enemiesObject[j]);
	}
	for (int i = 0; i < enemiesObject.size(); i++)/////////////////////
		for (int j = 0; j < WEAPON->size(); j++)
			COLLISION->checkCollision(enemiesObject[i], WEAPON->at(j));
	
	for (int i = 0; i < BLOOD->size(); i++)
	{
		BLOOD->at(i)->update();
	}
	for (int i = 0; i < doorObject.size(); i++)
		COLLISION->checkCollision(MEGAMAN, doorObject[i]);
	for (int i = 0; i < preventMoveCamera.size(); i++)
	{
		COLLISION->checkCollision(CAMERA, preventMoveCamera[i]);
	}

	for (int j = 0; j < enemiesObject.size(); j++)//////////////
	{
		enemiesObject[j]->updateLocation();
	}

	for (int i = 0; i < ENEMYBULLET->size(); i++)///////////////////////
	{
		ENEMYBULLET->at(i)->updateLocation();
	}

	for (int i = 0; i < ENEMYBULLET->size(); i++)
		ENEMYBULLET->at(i)->updateLocation();

	MEGAMAN->updateLocation();
	CAMERA->updateLocation();
	updateLocation();
}
void Map::updateLocation()
{
	xMap += CAMERA->dx;
	yMap += CAMERA->dy;
}
void Map::draw()
{
	RECT r;
	SetRect(&r, xMap, yMap, xMap + VIEWPORT_WIDTH, yMap + VIEWPORT_HEIGHT);
	mapSheetImg.RenderTexture(0, 0,&r);

	List<Enemy*> enemiesObject = CAMERA->objectsInCamera.enemies;
	List<Item*>itemObject = CAMERA->objectsInCamera.items;
	List<Door*>doorObject = CAMERA->objectsInCamera.doors;

	for (int j = 0; j < enemiesObject.size(); j++)
	{
		enemiesObject[j]->draw();
	}
	for (int i = 0; i < ENEMYBULLET->size(); i++)
		ENEMYBULLET->at(i)->draw();
	for (int i = 0; i < WEAPON->size(); i++)
		WEAPON->at(i)->draw();
	WEAPONSTATUS->draw();
	for (int i = 0; i < ENEMYBULLET->size(); i++)
	{
		ENEMYBULLET->at(i)->draw();
	}
	for (int i = 0; i < itemObject.size(); i++)
		itemObject[i]->draw();
	for (int i = 0; i < doorObject.size(); i++)
		doorObject[i]->draw();
	for (int i = 0; i < BLOOD->size(); i++)
		BLOOD->at(i)->draw();

}
