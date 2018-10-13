#include "Megaman.h"
#include"KeyGame.h"
#include"Map.h"

Megaman*Megaman::instance = 0;
Megaman * Megaman::getInstance()
{
	if (instance == 0)
		instance = new Megaman();
	return instance;
}

Megaman::Megaman()
{
	sprite = SPRITEMANAGER->sprites[SPR_MAIN];
	width = 35;
	height = 44;
	x = 115;
	y = 200;
}

void Megaman::update()
{
	//update vo hieu hoa key
	if (!KEY->canChangeKeyLeft && (KEY->keyRight|| KEY->keyJum))
		KEY->canChangeKeyLeft = true;
	if (!KEY->canChangeKeyRight && (KEY->keyLeft || KEY->keyJum))
		KEY->canChangeKeyRight = true;

	// vo hieu hoa key
	if (isOnGround) 
	{
		if (!KEY->canChangeKeyLeft)
			KEY->keyLeft = false;
		if (!KEY->canChangeKeyRight)
			KEY->keyRight = false;
		if ((!KEY->canChangeKeyLeft && direction == Left) || (!KEY->canChangeKeyRight && direction == Right))
			KEY->keySlide = false;
		if (!KEY->keyLeft && !KEY->keyRight)
			KEY->keyMove = false;
	}

	// update direction 
	if (KEY->keyLeft)
		direction = Left;
	if (KEY->keyRight)
		direction = Right;

	// update animation


	//update curFrame vs vy,dx,dy 
	//update truoc va cham : isOnGround, isCollision, isCollisionCross
	MovableObject::update();
}

void Megaman::updateLocation()
{
	x += dx;
	y += dy;
}

void Megaman::draw()
{
	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	int updateY = sprite->animates[curAnimation].frames[curFrame].height - height;
	yInViewport -= updateY;

	int trucQuay = xInViewport + width / 2;

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}
}

void Megaman::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_GROUND && nx != 0)
	{
		if (direction == Left && x == other->right())
			KEY->canChangeKeyLeft = false;
		else
			if(direction == Right && right() == other->x)
				KEY->canChangeKeyRight = false;
	}

	
	if(other->collisionType==CT_GROUND)
		MovableObject::onCollision(other, nx, ny);
}


Megaman::~Megaman()
{
}
