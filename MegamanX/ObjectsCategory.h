#pragma once
#include "List.h"
#include"BaseObject.h"
#include"Enemy.h"
#include"Item.h"
//add
class ObjectsCategory
{
public:
	List<BaseObject*> allObjects;
	List<BaseObject*>grounds;
	List<Enemy*> enemies;
	List<BaseObject*> preventMoveCameras;
	List<Item*>items;
	List<BaseObject*>traps;

	void add(BaseObject* object);
	void remove(BaseObject* object);

	ObjectsCategory(void);
	~ObjectsCategory(void);
};

