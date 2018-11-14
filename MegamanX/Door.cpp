#include "Door.h"
#include"Map.h"
#include"Megaman.h"

List<Door*>* Door::doors = 0;
void Door::update()
{
	if (opening)
	{
		if (curFrame < sprite->animates[0].nFrame - 1)
			curFrame++;
		else
			opening = false;
	}
	if (!opening && curFrame > 0 && MEGAMAN->x>right())
		curFrame--;
}

void Door::draw()
{
	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	sprite->draw(xInViewport, yInViewport, 0, curFrame);
}

void Door::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_PLAYER && !isOpened)
	{
		opening = true;
		isOpened = true;
	}
}

void Door::restore(BaseObject * obj)
{
	opening = false;
	isOpened = false;;
	DrawableObject::restore(obj);
}

Door::Door()
{
	sprite = SPRITEMANAGER->sprites[SPR_DOOR];
	collisionType = CT_DOOR;
	opening = false;
	isOpened = false;

	if (doors == 0)
		doors = new List<Door*>();
	doors->_Add(this);
}


Door::~Door()
{
	doors->_Remove(this);
	if (doors->size() == 0)
		delete doors;
}
