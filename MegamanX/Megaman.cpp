#include "Megaman.h"
#include"KeyGame.h"
#include"Map.h"
#include"GameTimeLoop.h"

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
	holdingAttack = false;
}

void Megaman::toAttack()
{
	if (curAnimation == MA_STAND)
	{
		curAnimation = MA_STAND_ATTACK;
		nextAnimation = MA_STAND_ATTACK;
	}
	else
		if (curAnimation == MA_JUMP)
		{
			curAnimation = MA_JUMP_ATTACK;
			nextAnimation = MA_JUMP_ATTACK;
		}
		else
			if (curAnimation == MA_RUN)
			{
				curAnimation = MA_RUN_ATTACK;
				nextAnimation = MA_RUN_ATTACK;
			}
			else
				if (curAnimation == MA_SLIDE)
				{
					curAnimation = MA_SLIDE_ATTACK;
					nextAnimation = MA_SLIDE_ATTACK;
				}
				else
					if (curAnimation == MA_WALL)
					{
						curAnimation = MA_WALL_ATTACK;
						nextAnimation = MA_WALL_ATTACK;
					}
					else
						if (curAnimation == MA_JUMPWALL)
						{
							curAnimation = MA_JUMPWALL_ATTACK;
							nextAnimation = MA_JUMPWALL_ATTACK;
						}
						else
							if (curAnimation == MA_HIGHJUMPWALL)
							{
								curAnimation = MA_HIGHJUMPWALL_ATTACK;
								nextAnimation = MA_HIGHJUMPWALL_ATTACK;
							}
							else
								if (curAnimation == MA_HIGHJUMP)
								{
									curAnimation = MA_HIGHJUMP_ATTACK;
									nextAnimation = MA_HIGHJUMP_ATTACK;
								}
}

void Megaman::toNormal()
{
	if (curAnimation == MA_STAND_ATTACK)
	{
		curAnimation = MA_STAND;
		nextAnimation = MA_STAND;
	}
	else
		if (curAnimation == MA_JUMP_ATTACK)
		{
			curAnimation = MA_JUMP;
			nextAnimation = MA_JUMP;
		}
		else
			if (curAnimation == MA_RUN_ATTACK)
			{
				curAnimation = MA_RUN;
				nextAnimation = MA_RUN;
			}
			else
				if (curAnimation == MA_SLIDE_ATTACK)
				{
					curAnimation = MA_SLIDE;
					nextAnimation = MA_SLIDE;
				}
				else
					if (curAnimation == MA_WALL_ATTACK)
					{
						curAnimation = MA_WALL;
						nextAnimation = MA_WALL;
					}
					else
						if (curAnimation == MA_JUMPWALL_ATTACK)
						{
							curAnimation = MA_JUMPWALL;
							nextAnimation = MA_JUMPWALL;
						}
						else
							if (curAnimation == MA_HIGHJUMPWALL_ATTACK)
							{
								curAnimation = MA_HIGHJUMPWALL;
								nextAnimation = MA_HIGHJUMPWALL;
							}
							else
								if (curAnimation == MA_HIGHJUMP_ATTACK)
								{
									curAnimation = MA_HIGHJUMP;
									nextAnimation = MA_HIGHJUMP;
								}
}

void Megaman::statusNormal()
{
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
		if ((curAnimation == MA_JUMPWALL || curAnimation == MA_HIGHJUMPWALL) && !KEY->keyJum && vy < 0)
			vy = 0;

		if ((curAnimation == MA_STAND || curAnimation == MA_RUN || curAnimation == MA_SLIDE) && vy > 0 || (curAnimation == MA_JUMPWALL && vy > 0))
			changeAction(MA_JUMP);
		else
			if (curAnimation == MA_HIGHJUMPWALL && vy > 0)
				changeAction(MA_HIGHJUMP);

			else
				if (curAnimation == MA_WALL)
				{
					if (KEY->keySlide && KEY->keyJum && canJump)
					{
						vx = -MEGAMAN_VX_WALL_H * direction;
						vy = MEGAMAN_VY_WALL_UP_H;
						changeAction(MA_HIGHJUMPWALL);
					}
					else
						if (KEY->keyJum && canJump)
						{
							vx = -MEGAMAN_VX_WALL * direction;
							vy = MEGAMAN_VY_WALL_UP;
							changeAction(MA_JUMPWALL);
						}
				}
				else
					if (curAnimation == MA_JUMP || curAnimation == MA_HIGHJUMP)
					{
						if (!KEY->keyJum && vy < 0)
							vy = 0.0f;
					}
	}
}

void Megaman::statusAttack()
{
	if (isOnGround)
	{
		if (curAnimation == MA_JUMP_ATTACK || curAnimation == MA_HIGHJUMP_ATTACK && vy >= 0)
		{
			changeAction(MA_STAND_ATTACK);
			return;
		}

		if (KEY->keyJum && KEY->keySlide && canJump)
		{
			vy = MEGAMAN_VY_JUMP;
			changeAction(MA_HIGHJUMP_ATTACK);
			canJump = false;
		}
		else
			if (KEY->keyJum && canJump)
			{
				vy = MEGAMAN_VY_JUMP;
				changeAction(MA_JUMP_ATTACK);
				canJump = false;
			}
			else
				if (KEY->keySlide && canSlide)
				{
					changeAction(MA_SLIDE_ATTACK);
				}
				else
					if ((KEY->keyLeft && canMoveLeft) || (KEY->keyRight&&canMoveRight))
					{
						if (curAnimation != MA_RUN_ATTACK)
							changeAction(MA_RUN_ATTACK);
					}
					else
						if (curAnimation != MA_STAND_ATTACK)
							changeAction(MA_STAND_ATTACK);
	}
	else
	{
		if ((curAnimation == MA_JUMPWALL_ATTACK || curAnimation == MA_HIGHJUMPWALL_ATTACK) && !KEY->keyJum && vy < 0)
			vy = 0;

		if ((curAnimation == MA_STAND_ATTACK || curAnimation == MA_RUN_ATTACK || curAnimation == MA_SLIDE_ATTACK) && vy > 0 || (curAnimation == MA_JUMPWALL_ATTACK && vy > 0))
			changeAction(MA_JUMP_ATTACK);
		else
			if (curAnimation == MA_HIGHJUMPWALL_ATTACK && vy > 0)
				changeAction(MA_HIGHJUMP_ATTACK);

			else
				if (curAnimation == MA_WALL_ATTACK)
				{
					if (KEY->keySlide && KEY->keyJum && canJump)
					{
						vx = -MEGAMAN_VX_WALL_H * direction;
						vy = MEGAMAN_VY_WALL_UP_H;
						changeAction(MA_HIGHJUMPWALL_ATTACK);
					}
					else
						if (KEY->keyJum && canJump)
						{
							vx = -MEGAMAN_VX_WALL * direction;
							vy = MEGAMAN_VY_WALL_UP;
							changeAction(MA_JUMPWALL_ATTACK);
						}
				}
				else
					if (curAnimation == MA_JUMP_ATTACK || curAnimation == MA_HIGHJUMP_ATTACK)
					{
						if (!KEY->keyJum && vy < 0)
							vy = 0.0f;
					}
	}
}

void Megaman::update()
{
	//update move, slide khi sat tuong
	if ((!canMoveLeft && direction == Left) || (!canMoveRight&&direction == Right))
		canSlide = false;
	if (!canMoveLeft && (KEY->keyRight || KEY->keyJum))
		canMoveLeft = true;
	if (!canMoveRight && (KEY->keyLeft || KEY->keyJum))
		canMoveRight = true;

	if (!KEY->keyJum)
		canJump = true;
	if (!KEY->keySlide)
		canSlide = true;
	

	//update vx,direction
	if (KEY->keyMove)
	{
		direction = KEY->keyLeft ? Left : Right;

		if (curAnimation == MA_JUMP || curAnimation == MA_RUN || curAnimation==MA_JUMP_ATTACK || curAnimation==MA_RUN_ATTACK)
		{
			vx = MEGAMAN_VX_RUN * direction;
		}
		else
			if (curAnimation == MA_SLIDE || curAnimation == MA_HIGHJUMP ||curAnimation == MA_SLIDE_ATTACK || curAnimation == MA_HIGHJUMP_ATTACK)
			{
				vx = MEGAMAN_VX_SLIDE * direction;
			}
			else
				if (curAnimation == MA_JUMPWALL || curAnimation == MA_JUMPWALL_ATTACK)
				{
					if (vy < 0)
						vx+=direction* MEGAMAN_AX*GAME_TIME->frameTime;
					else
						vx = direction * MEGAMAN_VX_RUN;
				}
				else
					if (curAnimation == MA_HIGHJUMPWALL || curAnimation == MA_HIGHJUMPWALL_ATTACK)
					{
						if (vy < 0)
							vx += direction* MEGAMAN_AX * GAME_TIME->frameTime;
						else
							vx = MEGAMAN_VX_SLIDE * direction;
					}
					else
						if (curAnimation == MA_WALL || curAnimation == MA_WALL_ATTACK)
							vx = MEGAMAN_VX_RUN * direction;
	}
	else
		if (curAnimation == MA_SLIDE || curAnimation == MA_SLIDE_ATTACK)
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

	if (timeAttack.curLoop > 0 && timeAttack.curLoop < 20)
	{
		if (curAnimation != MA_STAND_ATTACK && curAnimation != MA_JUMP_ATTACK && curAnimation != MA_RUN_ATTACK && curAnimation != MA_SLIDE_ATTACK
			&& curAnimation != MA_WALL_ATTACK && curAnimation != MA_JUMPWALL_ATTACK && curAnimation != MA_HIGHJUMPWALL_ATTACK && curAnimation != MA_HIGHJUMP_ATTACK)
			MEGAMAN->toAttack();
		
		statusAttack();
		if (KEY->keyAttack)
			if (holdingAttack)
				timeAttack.curLoop++;
			else
			{
				timeAttack.curLoop = 1;
				holdingAttack = true;
			}
		if (!KEY->keyAttack)
		{
			timeAttack.curLoop++;
			holdingAttack = false;
		}
		return;
	}

	if (KEY->keyAttack)
	{
		timeAttack.curLoop++;
		
		if (timeAttack.curLoop >= 20)
		{
			toNormal();
			statusNormal();
		}
	}
	else
	{
		if (timeAttack.curLoop >= 20 && timeAttack.curLoop < 50)
		{

		}
		else
			if (timeAttack.curLoop >= 50)
			{

			}
		timeAttack.start();
		
		statusNormal();
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
		if (direction == Left && x == other->right())
			canMoveLeft = false;
		else
			if (direction == Right && right() == other->x)
				canMoveRight = false;
	}
	
	//on wall
	if (((nx == 1 && KEY->keyLeft) || (nx == -1 && KEY->keyRight)) && curAnimation != MA_RUN && curAnimation != MA_SLIDE && curAnimation != MA_STAND && other->collisionType == CT_GROUND
		&& curAnimation != MA_RUN_ATTACK && curAnimation != MA_SLIDE_ATTACK && curAnimation != MA_STAND_ATTACK)
	{
		if (timeAttack.curLoop > 0 && timeAttack.curLoop < 100)
			curAnimation = MA_WALL_ATTACK;
		else
			curAnimation = MA_WALL;
		curFrame = 0;
		vy = MEGAMAN_VY_WALL_DOWN;
	}

	// update .....
	if (other->collisionType == CT_GROUND)
		MovableObject::onCollision(other, nx, ny);

	if (dy > 0 &&curAnimation!=MA_WALL && curAnimation!=MA_JUMPWALL && curAnimation!=MA_HIGHJUMPWALL 
		&& curAnimation != MA_WALL_ATTACK && curAnimation != MA_JUMPWALL_ATTACK && curAnimation != MA_HIGHJUMPWALL_ATTACK)
		canJump = false;
}

Megaman::~Megaman()
{
}
