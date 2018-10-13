#include "MovableObject.h"

void MovableObject::updateVelocity()
{
	vy += ay * GAME_TIME->frameTime;
	dx = vx * GAME_TIME->frameTime;
	dy = vy * GAME_TIME->frameTime;
}

void MovableObject::update()
{
	isOnGround = false;
	updateVelocity();
	DrawableObject::update();
}

void MovableObject::draw()
{
	DrawableObject::draw();
}

void MovableObject::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_GROUND)
	{
		if (ny == -1)
			isOnGround = true;

		COLLISION->preventMove(this, other);

		if (ny < 0)
			vy = 0;
	}
}

MovableObject::MovableObject()
{
	direction = Right;
	ay = GRAVITY;
}

MovableObject::~MovableObject()
{
}