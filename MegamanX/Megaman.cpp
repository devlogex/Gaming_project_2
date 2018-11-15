#include "Megaman.h"
#include"KeyGame.h"
#include"Map.h"
#include"GameTimeLoop.h"
#include"Weapon.h"
#include"Weapon_Simple.h"
#include"Weapon_Medium.h"
#include"Weapon_Large.h"
#include"Weapon_Status.h"
#include"Camera.h"
#include"Enemy.h"
#include"Enemy_Bullet.h"
#include"Door.h"
#include"Stage.h"

Megaman*Megaman::instance = 0;
Megaman * Megaman::getInstance()
{
	if (instance == 0)
		instance = new Megaman();
	return instance;
}

Megaman::Megaman()
{
	id = 0;
	sprite = SPRITEMANAGER->sprites[SPR_MAIN];
	collisionType = CT_PLAYER;
	life = MEGAMAN_LIFE;
	updateY = 0;
	width = 30;
	height = 34;
	x = CAMERA->xCenter()-width;
	y = CAMERA->yCenter();
	curAnimation = MA_APPEAR;
	curFrame = 0;
	direction = Right;
	inviolable = false;
	isDraw = true;
	numberOfAlive = 3;

	timeBeDamaged.init(0.1, 11);
	timeBeDamaged.start();

	timeWeaponAppear.init(0.13, 1);
	timeWeaponAppear.start();

	timeAttack.init(1, 100);
	timeAttack.start();

	timeDeath.init(0.2, 5);
	timeDeath.start();

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
						ax = direction * MEGAMAN_AX;
						vy = MEGAMAN_VY_WALL_UP_H;
						changeAction(MA_HIGHJUMPWALL);
					}
					else
						if (KEY->keyJum && canJump)
						{
							vx = -MEGAMAN_VX_WALL * direction;
							ax = direction * MEGAMAN_AX;
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

void Megaman::updateVX()
{
	if (KEY->keyMove)
	{
		direction = KEY->keyLeft ? Left : Right;

		if (curAnimation == MA_JUMP || curAnimation == MA_RUN || curAnimation == MA_JUMP_ATTACK || curAnimation == MA_RUN_ATTACK)
		{
			vx = MEGAMAN_VX_RUN * direction;
		}
		else
			if (curAnimation == MA_SLIDE || curAnimation == MA_HIGHJUMP || curAnimation == MA_SLIDE_ATTACK || curAnimation == MA_HIGHJUMP_ATTACK)
			{
				vx = MEGAMAN_VX_SLIDE * direction;
			}
			else
				if (curAnimation == MA_JUMPWALL || curAnimation == MA_JUMPWALL_ATTACK)
				{
					if (vy < 0 && ax*direction>=0)
						vx += ax*GAME_TIME->frameTime;
					else
						vx = direction * MEGAMAN_VX_RUN;
				}
				else
					if (curAnimation == MA_HIGHJUMPWALL || curAnimation == MA_HIGHJUMPWALL_ATTACK)
					{
						if (vy < 0 && ax*direction >= 0)
							vx += ax * GAME_TIME->frameTime;
						else
							vx = MEGAMAN_VX_SLIDE * 2 / 3 * direction;
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
	if (curAnimation == MA_STAND || curAnimation==MA_DAMAGED)
		vx = 0;
}

void Megaman::updateBlock()
{
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
	
}

void Megaman::updateBeforeHandle()
{
	isOnGround = false;
	updateVelocity();
	BaseObject::update();
	if (delayAnimation.canCreateFrame())
	{
		if (curAnimation != nextAnimation)
		{
			curAnimation = nextAnimation;
			curFrame = 0;
		}
		else
			if (curFrame++ >= sprite->animates[curAnimation].nFrame - 1)
			{
				if (curAnimation == MA_STAND || curAnimation == MA_RUN || curAnimation == MA_STAND_ATTACK || curAnimation == MA_RUN_ATTACK)
					curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
				else
					curFrame = sprite->animates[curAnimation].nFrame - 1;

				if (curAnimation == MA_SLIDE ||curAnimation==MA_SLIDE_ATTACK)
					MEGAMAN->canSlide = false;
				if (curAnimation == MA_JUMPWALL || curAnimation == MA_HIGHJUMPWALL)
					MEGAMAN->canJump = false;
			}
	}
}

void Megaman::update()
{
	if (!alive)
		return;

	updateStage();
	if (Stage::updating)
		return;

	//update move, slide khi sat tuong
	updateBlock();

	//update vx,direction
	updateVX();

	//time weapon
	timeWeaponAppear.canCreateFrame();

	//update animetion
	updateAnimation();

	//update before handle event (reset)
	updateBeforeHandle();
}

void Megaman::updateAnimation()
{
	if (timeBeDamaged.curLoop > 0 && timeBeDamaged.curLoop < 50)
	{
		if (curAnimation != MA_DAMAGED)
			changeAction(MA_DAMAGED);
		timeBeDamaged.curLoop++;
		inviolable = true;
		return;
	}
	else
		if (timeBeDamaged.curLoop >= 50 && timeBeDamaged.curLoop < 100)
		{
			timeBeDamaged.curLoop++;
		}
		else
		{
			timeBeDamaged.start();
			inviolable = false;
		}

	if (timeAttack.curLoop > 0 && timeAttack.curLoop < 15)
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

		if (timeAttack.curLoop == 1 && timeWeaponAppear.isTerminated())
		{
			WEAPON->_Add(new Weapon_Simple());
			timeWeaponAppear.start();
		}

		return;
	}


	if (KEY->keyAttack)
	{
		timeAttack.curLoop++;

		if (timeAttack.curLoop >= 50)
		{
			toNormal();
			statusNormal();
			WEAPONSTATUS->allowDraw = true;
			
			if (timeAttack.curLoop >= 100)
				WEAPONSTATUS->changeAction(WS_LARGE);
		}

	}
	else
	{
		if (timeAttack.curLoop >= 50 && timeAttack.curLoop < 100)
		{
			WEAPON->_Add(new Weapon_Medium());
			timeWeaponAppear.start();
		}
		else
			if (timeAttack.curLoop >= 100)
			{
				WEAPON->_Add(new Weapon_Large());
				timeWeaponAppear.start();
			}
		timeAttack.start();
		WEAPONSTATUS->allowDraw = false;

		statusNormal();
	}
}

void Megaman::updateStage()
{
	if (x < CAMERA->x && dx < 0)
		dx = 0;
	if (right() > CAMERA->right() && !Stage::updating)
		Stage::loadStageNext();
	if (Stage::updating)
	{
		if (delayAnimation.canCreateFrame())
		{
			if (curFrame++ >= sprite->animates[curAnimation].nFrame - 1)
			{
				if (curAnimation == MA_STAND || curAnimation == MA_RUN || curAnimation == MA_STAND_ATTACK || curAnimation == MA_RUN_ATTACK)
					curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
				else
					curFrame = sprite->animates[curAnimation].nFrame - 1;
			}
		}
		dx = 0.3;
	}
}

void Megaman::updateLocation()
{
	if (x <= CAMERA->x && !Stage::updating && dx<0)
		dx = 0;
	x += dx;
	y += dy;
}

void Megaman::draw()
{
	if (!alive)
		return;

	if (timeBeDamaged.curLoop > 0 && timeBeDamaged.curLoop < 100)
		isDraw = !isDraw;
	else
		isDraw = true;
	if (!isDraw)
		return;

	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	updateY = sprite->animates[curAnimation].frames[curFrame].height - height;
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

void Megaman::restore(BaseObject * obj)
{
	setSprite();
	life = MEGAMAN_LIFE;
	alive = true;
	curAnimation = 0;
	nextAnimation = 0;
	curFrame = 0;
	timeAttack.start();
	timeWeaponAppear.start();
	timeBeDamaged.start();
}

void Megaman::onCollision(BaseObject * other, int nx, int ny)
{
	// can't move,slide khi sat tuong
	if ((other->collisionType == CT_GROUND || (other->collisionType == CT_DOOR && !((Door*)other)->opening)) 
		&& nx != 0 && (curAnimation == MA_RUN || curAnimation == MA_SLIDE))
	{
		if (direction == Left && x == other->right())
			canMoveLeft = false;
		else
			if (direction == Right && right() == other->x)
				canMoveRight = false;
	}
	
	//on wall
	if (((nx == 1 && KEY->keyLeft) || (nx == -1 && KEY->keyRight)) && curAnimation != MA_RUN && curAnimation != MA_SLIDE && curAnimation != MA_STAND && other->collisionType == CT_GROUND
		&& curAnimation != MA_RUN_ATTACK && curAnimation != MA_SLIDE_ATTACK && curAnimation != MA_STAND_ATTACK && curAnimation!=MA_DAMAGED)
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
	if (other->collisionType == CT_DOOR && !((Door*)other)->opening)
	{
		COLLISION->preventMove(this, other);
	}

	//block jump
	if (dy > 0 && curAnimation!=MA_WALL && curAnimation != MA_WALL_ATTACK)
		canJump = false;

}

void Megaman::onAABBCheck(BaseObject * other)
{
	if ((other->collisionType == CT_ENEMY || other->collisionType==CT_TRAP) && !inviolable)
	{
		timeBeDamaged.curLoop++;
		if (other->collisionType == CT_ENEMY)
		{
			if (id == -5)
				life -= ((Enemy_Bullet*)other)->damage;
			else
				life -= ((Enemy*)other)->damage;
		}
		else
			life = 0;

		if (life <= 0)
		{
			alive = false;
			numberOfAlive -= 1;
		}
	}
	if (other->collisionType == CT_ITEM)
	{
		life = MEGAMAN_LIFE;
	}
}

Megaman::~Megaman()
{
}
