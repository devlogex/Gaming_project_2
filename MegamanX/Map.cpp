#include "Map.h"
#include"DrawableObject.h"
#include"Camera.h"
#include"Megaman.h"
#include"Weapon.h"
#include"Weapon_Status.h"

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

		switch (id)
		{
		
		
		default:
			objects[i] = new BaseObject();
			break;
		}

		objects[i]->id = id;
		objects[i]->x = x;
		objects[i]->y = y;
		objects[i]->width = width;
		objects[i]->height = height;

	/*	if (id >= 0)
		{
			DrawableObject* drawableObject = (DrawableObject*)objects[i];
			drawableObject->setSprite();
		}*/

		//objects[i]->getFromObject(objects[i]);
	}

	fs.close();
}

void Map::init(const char * mapSheetPath, const char * objectsPath, const char * quadtreePath)
{
	mapSheetImg.Init(mapSheetPath, D3DCOLOR_XRGB(0, 0, 0));
	initObjects(objectsPath);
	quadtree.init(quadtreePath, objects);
}

void Map::restoreAllObject()
{
}

void Map::update()
{
	CAMERA->update();
	quadtree.update();
	MEGAMAN->update();
	WEAPONSTATUS->update();

	for (int i = 0; i < WEAPON->size(); i++)
	{
		WEAPON->at(i)->update();
	}

	List<BaseObject*> groundsObject = CAMERA->objectsInCamera.grounds;

	for (int i = 0; i < groundsObject.size(); i++)
		COLLISION->checkCollision(MEGAMAN, groundsObject[i]);

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
}
