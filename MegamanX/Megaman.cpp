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
	width = 30;
	height = 34;
	x = 367;
	y = 361;

	canJump = true;
	canSlide = true;
	canMoveLeft = true;
	canMoveRight = true;
}

void Megaman::update()
{
	//update move, slide khi sat tuong
	if ((!canMoveLeft && direction == Left) || (!canMoveRight&&direction == Right))
		canSlide = false;

	if (!KEY->keyJum)
		canJump = true;
	if (!KEY->keySlide)
		canSlide = true;


	//update vx,direction
	if (KEY->keyMove)
	{
		if (curAnimation == MA_JUMP || curAnimation == MA_RUN)
		{
			direction = KEY->keyLeft ? Left : Right;
			vx = MEGAMAN_VX_RUN * direction;
		}
		else
			if (curAnimation == MA_SLIDE && curAnimation == MA_HIGHJUMP)
			{
				direction = KEY->keyLeft ? Left : Right;
				vx = MEGAMAN_VX_SLIDE * direction;
			}
			else
				if (curAnimation == MA_JUMPWALL && vy < 0)
					vx = MEGAMAN_VX_RUN * direction;
				else
					if (curAnimation == MA_HIGHJUMPWALL)
						vx = MEGAMAN_VX_SLIDE * direction;
					else
						if (curAnimation == MA_WALL)
							vx = -MEGAMAN_VX_RUN * direction;
	}
	else
		if (curAnimation == MA_SLIDE)
		{
			vx = MEGAMAN_VX_SLIDE * direction;
		}
		else
			vx = 0;

	updateAnimation();

	MovableObject::update();
}

void Megaman::updateAnimation()
{
	if (curAnimation == MA_APPEAR)
		if (curFrame == sprite->animates[curAnimation].nFrame - 1)
			changeAction(MA_STAND);

	if (isOnGround)
	{
		if (curAnimation == MA_JUMP || curAnimation == MA_HIGHJUMP && vy >= 0)
		{
			changeAction(MA_STAND);
			return;
		}

		if (KEY->keyJum && KEY->keySlide && canJump)
		{
			vy = MEGAMAN_VY_JUMP;
			changeAction(MA_HIGHJUMP);
			canJump = false;
		}
		else
			if (KEY->keyJum && canJump)
			{
				vy = MEGAMAN_VY_JUMP;
				changeAction(MA_JUMP);
				canJump = false;
			}
			else
				if (KEY->keySlide && canSlide)
				{
					changeAction(MA_SLIDE);
				}
				else
					if ((KEY->keyLeft && canMoveLeft) || (KEY->keyRight&&canMoveRight))
					{
						if (curAnimation != MA_RUN)
							changeAction(MA_RUN);
					}
					else
						if (curAnimation != MA_STAND)
							changeAction(MA_STAND);
	}
	else
	{
		if (curAnimation == MA_STAND || curAnimation == MA_RUN || curAnimation == MA_SLIDE ||
			((curAnimation == MA_JUMP || curAnimation == MA_HIGHJUMPWALL) && vy >= 0 && !KEY->keyMove))
			changeAction(MA_JUMP);
		else
			if (curAnimation == MA_WALL)
			{
				if (KEY->keySlide && KEY->keyJum && canJump)
				{
					vy = MEGAMAN_VY_JUMP;
					changeAction(MA_HIGHJUMPWALL);
					canJump = false;
				}
				else
					if (KEY->keyJum && canJump)
					{
						vy = MEGAMAN_VY_JUMP;
						changeAction(MA_JUMPWALL);
						canJump = false;
					}
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
	DrawableObject::draw();
}

void Megaman::onCollision(BaseObject * other, int nx, int ny)
{
	// can't move,slide khi sat tuong
	if (other->collisionType == CT_GROUND && nx != 0)
	{
		if (KEY->keyLeft && direction == Left)
			canMoveLeft = false;
		else
			if (KEY->keyRight && direction == Right)
				canMoveRight = false;
			else
			{
				canMoveLeft = true;
				canMoveRight = true;
			}
	}

	// update .....
	if (other->collisionType == CT_GROUND)
		MovableObject::onCollision(other, nx, ny);

	//wall
	if (other->collisionType == CT_GROUND && nx != 0 && isOnGround)
	{
		changeAction(MA_WALL);
		vy = MEGAMAN_VY_WALL;
		direction = direction == Left ? Right : Left;
	}
}


Megaman::~Megaman()
{
}
