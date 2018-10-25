#pragma once
#include "List.h"
#include"BaseObject.h"
#include"Enemy.h"
//add
class ObjectsCategory
{
public:
	List<BaseObject*> allObjects;
	List<BaseObject*>grounds;
	List<Enemy*> enemies;

	void add(BaseObject* object);
	void remove(BaseObject* object);

	ObjectsCategory(void);
	~ObjectsCategory(void);
};

