#pragma once
#include "Texture.h"
#include "BaseObject.h"
#include "QuadTree.h"
#include <fstream>
using namespace std;

class Map
{
public:
	static Map* curMap;

	float viewportWidth, viewportHeight;
	float xMap, yMap;
	Texture mapSheetImg;

	QuadTree quadtree;
	int nObjects;
	BaseObject** objects;


	void convertToViewportPos(int xInMap, int yInMap, int& xViewport, int& yViewport);
	void render();
	void initObjects(const char* objectsPath);
	void init(const char* mapSheetPath, const char* objectsPath, const char* quadtreePath);
	//void initStage(const char* stageInfoPath);

	void restoreAllObject();
	void update();
	void draw();
	void updateLocation();

	Map();
	~Map();
};

