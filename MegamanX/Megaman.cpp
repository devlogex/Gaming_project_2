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
	x = 334;
	y = 373;

	blockDirection = false;
}

void Megaman::update()
{
	//update blockKey
	if (KEY->blockKeyLeft && (KEY->keyRight || KEY->keyJum))
		KEY->blockKeyLeft = false;
	if (KEY->blockKeyRight && (KEY->keyLeft || KEY->keyJum))
		KEY->blockKeyRight = false;

	if (!KEY->keyJum)
		KEY->blockKeyJump = false;
	if (!KEY->keySlide)
		KEY->blockKeySlide = false;


	// block key
	if (isOnGround)
	{
		if (KEY->blockKeyLeft)
			KEY->keyLeft = false;
		if (KEY->blockKeyRight)
			KEY->keyRight = false;
		if ((KEY->blockKeyLeft && direction == Left) || (KEY->blockKeyRight && direction == Right))
			KEY->keySlide = false;
		if (!KEY->keyLeft && !KEY->keyRight)
			KEY->keyMove = false;
	}

	if (KEY->blockKeyJump)
		KEY->keyJum = false;
	if (KEY->blockKeySlide)
		KEY->keySlide = false;

	// update direction 
	if (blockDirection)
	{
		if ((KEY->keyLeft && direction == Right) || (KEY->keyRight && direction == Left) && vx != 0)
		{
			if (curAnimation == MA_JUMP)
				vx = vx - direction * MEGAMAN_VX_RUN * GAME_TIME->frameTime;
			else
				if (curAnimation == MA_HIGHJUMP)
					vx = vx - direction * MEGAMAN_VX_SLIDE * GAME_TIME->frameTime;
		}
		else
			blockDirection = false;
	}
	else
	{
		if (KEY->keyLeft)
			direction = Left;
		if (KEY->keyRight)
			direction = Right;
		if (KEY->keyMove)
		{
			if (curAnimation == MA_SLIDE || curAnimation == MA_HIGHJUMP)
				vx = direction * MEGAMAN_VX_SLIDE;
			else
				vx = direction * MEGAMAN_VX_RUN;
		}
		else
			if (!curAnimation == MA_SLIDE)
				vx = 0;
	}



	// update animation
	updateAnimation();

	//update curFrame vs vy,dx,dy 
	//update truoc va cham : isOnGround, isCollision, isCollisionCross
	MovableObject::update();
}

void Megaman::updateAnimation()
{
	if (isOnGround)
	{
		if (curAnimation == MA_JUMP || curAnimation == MA_HIGHJUMP)
		{
			if (KEY->keyMove)
			{
				vx = direction * MEGAMAN_VX_RUN;
				if (curAnimation != MA_RUN)
				{
					changeAction(MA_RUN);
				}
			}
			else
				if (curAnimation != MA_STAND)
				{
					changeAction(MA_STAND);
					vx = 0.0f;
				}

			return;
		}

		if (KEY->keySlide && KEY->keyJum)
		{
			if (KEY->keyMove)
			{
				vx = direction * MEGAMAN_VX_SLIDE;
				vy = MEGAMAN_VY_JUMP;
			}
			else
			{
				vx = 0;
				vy = MEGAMAN_VY_JUMP;
			}
			changeAction(MA_HIGHJUMP);
		}
		else
			if (KEY->keySlide)
			{
				if (curAnimation != MA_SLIDE && curAnimation != MA_JUMP)
				{
					vx = direction * MEGAMAN_VX_SLIDE;
					changeAction(MA_SLIDE);
				}
			}
			else
				if (KEY->keyJum)
				{
					if (curAnimation != MA_JUMP)
					{
						vy = MEGAMAN_VY_JUMP;
						changeAction(MA_JUMP);
					}
				}
				else
					if (KEY->keyMove)
					{
						vx = direction * MEGAMAN_VX_RUN;
						if (curAnimation != MA_RUN)
						{
							changeAction(MA_RUN);
						}
					}
					else
						if (curAnimation != MA_STAND)
						{
							changeAction(MA_STAND);
							vx = 0.0f;
						}
	}
	else
	{
		if (curAnimation == MA_CLIMB)
		{
			if (KEY->keyJum && KEY->keySlide)
			{
				direction = direction == Left ? Right : Left;
				vx = direction * MEGAMAN_VX_SLIDE;
				vy = MEGAMAN_VY_JUMP;
				changeAction(MA_HIGHJUMP);

				//block direction
				blockDirection = true;
			}
			else
				if (KEY->keyJum)
				{
					direction = direction == Left ? Right : Left;
					vx = direction * MEGAMAN_VX_RUN;
					vy = MEGAMAN_VY_JUMP;
					changeAction(MA_JUMP);

					//block direction
					blockDirection = true;
				}
		}
		else
		{
			if (curAnimation == MA_HIGHJUMP && KEY->keyMove && !blockDirection)
				vx = direction*MEGAMAN_VX_SLIDE;
			else
				if (curAnimation == MA_JUMP)
				{
					if (!KEY->keyJum && vy < 0)
					{
						vy = 0.0f;
					}
				}
				else
					changeAction(MA_JUMP);

		}
	}
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
	// block keyMove and keySlide
	if (other->collisionType == CT_GROUND && nx != 0)
	{
		if (direction == Left && x == other->right())
			KEY->blockKeyLeft = true;
		else
			if (direction == Right && right() == other->x)
				KEY->blockKeyRight = true;
	}

	// climb
	if (((nx == 1 && KEY->keyLeft) || (nx == -1 && KEY->keyRight)) && curAnimation != MA_RUN && curAnimation != MA_SLIDE && curAnimation != MA_STAND && other->collisionType == CT_GROUND)
	{
		vy = 0;

		if (curAnimation != MA_CLIMB)
		{
			curAnimation = MA_CLIMB;
			curFrame = 0;
		}
	}

	// update .....
	if (other->collisionType == CT_GROUND)
		MovableObject::onCollision(other, nx, ny);

	//block keyJump
	if (dy > 0)
		KEY->blockKeyJump = true;
}


Megaman::~Megaman()
{
}
