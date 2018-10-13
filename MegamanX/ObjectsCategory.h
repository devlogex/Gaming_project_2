#pragma once
#include "List.h"
#include"BaseObject.h"

//add
class ObjectsCategory
{
public:
	List<BaseObject*> allObjects;
	List<BaseObject*>grounds;

	void add(BaseObject* object);
	void remove(BaseObject* object);

	ObjectsCategory(void);
	~ObjectsCategory(void);
};

