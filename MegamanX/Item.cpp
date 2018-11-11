#include "Item.h"
#include"SpriteManager.h"
#include"MovableObject.h"
#include"Map.h"

void Item::draw()
{
	if (alive)
	{
		int xInViewport, yInViewport;
		Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

		sprite->draw(xInViewport, yInViewport, 0, 0);
	}
}

void Item::update()
{
}

void Item::onAABBCheck(BaseObject * other)
{
	if (other->collisionType == CT_PLAYER && alive)
		alive = false;
}

void Item::onCollision(BaseObject * other, int nx, int ny)
{
}

Item::Item()
{
	collisionType = CT_ITEM;

	vx = 0;
	vy = 0;
	dx = 0;
	dy = 0;
}


Item::~Item()
{
}
