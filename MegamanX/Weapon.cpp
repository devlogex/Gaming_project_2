#include "Weapon.h"
#include"Megaman.h"
#include"WeaponLocation.h"
#include"Map.h"
List<Weapon*>*Weapon::weapons = 0;
List<Weapon*>* Weapon::getWeapons()
{
	if (weapons == 0)
		weapons = new List<Weapon*>();
	return weapons;
}

void Weapon::update()
{
	dx = vx * GAME_TIME->frameTime;
	dy = 0;

	updateLocation();
}

void Weapon::draw()
{
	int xInViewport, yInViewport;
	Map::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	int trucQuay = xInViewport;

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame,true);

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}
}

void Weapon::updateLocation()
{
	x += dx;
	y += dy;
}

void Weapon::onAABBCheck(BaseObject * other)
{
	if (other->collisionType == CT_ENEMY)
		WEAPON->_Remove(this);
}

Weapon::Weapon()
{
	collisionType = CT_WEAPON;
	allowDelete = false;

	if (MEGAMAN->curAnimation != MA_WALL_ATTACK)
		direction = MEGAMAN->direction;
	else
		direction = MEGAMAN->direction == Left ? Right : Left;

	vx = WEAPON_VX * direction;
	vy = 0;

	int xInSprite = MEGAMAN->curAnimation == MA_STAND_ATTACK ? WEAPONLOCATION->ptsStand[MEGAMAN->curFrame].x : MEGAMAN->curAnimation == MA_RUN_ATTACK ? WEAPONLOCATION->ptsRun[MEGAMAN->curFrame].x
		: MEGAMAN->curAnimation == MA_JUMP_ATTACK ? WEAPONLOCATION->ptsJump[MEGAMAN->curFrame].x : MEGAMAN->curAnimation == MA_HIGHJUMP_ATTACK ? WEAPONLOCATION->ptsHighJump[MEGAMAN->curFrame].x
		: MEGAMAN->curAnimation == MA_SLIDE_ATTACK ? WEAPONLOCATION->ptsSlide[MEGAMAN->curFrame].x : MEGAMAN->curAnimation == MA_WALL_ATTACK ? WEAPONLOCATION->ptsWall[MEGAMAN->curFrame].x
		: MEGAMAN->curAnimation == MA_JUMPWALL_ATTACK ? WEAPONLOCATION->ptsJumpWall[MEGAMAN->curFrame].x : /*MEGAMAN->curAnimation == MA_HIGHJUMPWALL_ATTACK ?*/ WEAPONLOCATION->ptsHighJumpWall[MEGAMAN->curFrame].x;
	int yInSprite = MEGAMAN->curAnimation == MA_STAND_ATTACK ? WEAPONLOCATION->ptsStand[MEGAMAN->curFrame].y : MEGAMAN->curAnimation == MA_RUN_ATTACK ? WEAPONLOCATION->ptsRun[MEGAMAN->curFrame].y
		: MEGAMAN->curAnimation == MA_JUMP_ATTACK ? WEAPONLOCATION->ptsJump[MEGAMAN->curFrame].y : MEGAMAN->curAnimation == MA_HIGHJUMP_ATTACK ? WEAPONLOCATION->ptsHighJump[MEGAMAN->curFrame].y
		: MEGAMAN->curAnimation == MA_SLIDE_ATTACK ? WEAPONLOCATION->ptsSlide[MEGAMAN->curFrame].y : MEGAMAN->curAnimation == MA_WALL_ATTACK ? WEAPONLOCATION->ptsWall[MEGAMAN->curFrame].y
		: MEGAMAN->curAnimation == MA_JUMPWALL_ATTACK ? WEAPONLOCATION->ptsJumpWall[MEGAMAN->curFrame].y : /*MEGAMAN->curAnimation == MA_HIGHJUMPWALL_ATTACK ?*/ WEAPONLOCATION->ptsHighJumpWall[MEGAMAN->curFrame].y;
	
	if (MEGAMAN->curAnimation != MA_WALL_ATTACK)
	{
		if (direction == Left)
		{
			x = MEGAMAN->x + MEGAMAN->width - xInSprite;
			y = MEGAMAN->y - MEGAMAN->updateY + yInSprite;
		}
		else
		{
			x = MEGAMAN->x + xInSprite;
			y = MEGAMAN->y - MEGAMAN->updateY + yInSprite;
		}
	}
	else
	{
		if (direction == Right)
		{
			x = MEGAMAN->x + MEGAMAN->width - xInSprite;
			y = MEGAMAN->y - MEGAMAN->updateY + yInSprite;
		}
		else
		{
			x = MEGAMAN->x + xInSprite;
			y = MEGAMAN->y - MEGAMAN->updateY + yInSprite;
		}
	}
}


Weapon::~Weapon()
{
}
