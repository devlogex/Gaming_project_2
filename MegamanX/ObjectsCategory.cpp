#include "ObjectsCategory.h"

void ObjectsCategory::add(BaseObject* object)
{
	switch (object->collisionType)
	{
	case CT_GROUND:
		grounds._Add(object);
		break;
	case CT_ENEMY:
		enemies._Add((Enemy*)object);
		break;
	default:
		break;
	}
	allObjects._Add(object);
}

void ObjectsCategory::remove(BaseObject* object)
{
	switch (object->collisionType)
	{
	case CT_GROUND:
		grounds._Remove(object);
		break;
	case CT_ENEMY:
		enemies._Remove((Enemy*)object);
		break;
	default:
		break;
	}
	allObjects._Remove(object);
}

ObjectsCategory::ObjectsCategory(void)
{
}

ObjectsCategory::~ObjectsCategory(void)
{
}
