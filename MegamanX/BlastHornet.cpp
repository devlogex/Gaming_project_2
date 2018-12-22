#include "BlastHornet.h"
#include"Megaman.h"
#include"Map.h"
#include"Enemy_Bullet.h"
#include"BlastHornet_Bullet.h"
#include"BlastHornet_Wing.h"

BlastHornet*BlastHornet::instance = 0;
BlastHornet * BlastHornet::getInstance()
{
	if (instance == 0)
		instance = new BlastHornet();
	return instance;
}
void BlastHornet::update()
{
	if (!alive)
		return;

	updateV();
	updateAnimation();
	updateBeforeHandle();

	BLASTHORNET_WING->update();
}
void BlastHornet::updateAnimation()
{
	if (curAnimation == BHA_APPEAR && timeAppear.isTerminated())
		changeAction(BHA_PRICK);
	else
		if (curAnimation == BHA_SHOT)
		{
			if (curFrame == sprite->animates[curAnimation].nFrame - 1 && !timeShot.isTerminated())
				timeShot.canCreateFrame();
			else
				if (timeShot.isTerminated() && !blockBullet)
				{
					ENEMYBULLET->_Add(new BlastHornet_Bullet(30, 0));
					ENEMYBULLET->_Add(new BlastHornet_Bullet(30, 10));
					ENEMYBULLET->_Add(new BlastHornet_Bullet(30, 15));
					ENEMYBULLET->_Add(new BlastHornet_Bullet(30, 25));
					ENEMYBULLET->_Add(new BlastHornet_Bullet(30, 35));
					blockBullet = true;
					changeAction(BHA_RESHOT);
				}
		}
		else
			if (curAnimation == BHA_RESHOT && curFrame == sprite->animates[curAnimation].nFrame - 1)
			{
				changeAction(BHA_FLY_HALF);
				blockBullet = false;
			}
			else
				if (curAnimation == BHA_FLY_FULL)
				{
					if (indexFlyFull == -1 && (dx>0 && x >= ptsFly[0].x)||(dx<0 && x<=ptsFly[0].x))
					{
						indexFlyFull = 0;
						dy = 5;
						dx = 0;
					}
					else
						if (indexFlyFull == 0 &&  x >= ptsFly[1].x)
						{
							indexFlyFull = 1;
						}
						else
							if (indexFlyFull == 1 && x <= ptsFly[0].x)
							{
								indexFlyFull = 0;
							}
				}


}
void BlastHornet::updateV()
{
	if (curAnimation == BHA_PRICK && curFrame == sprite->animates[curAnimation].nFrame - 1 && vy<=0)
	{
		if (MEGAMAN->x - x >= 0)
		{
			vx = MEGAMAN->right() - x;
			vy = MEGAMAN->y - y;
		}
		else
		{
			vx = MEGAMAN->x - x-width;
			vy = MEGAMAN->y - y;
		}
		fixV(vx, vy, 90);
	}
	else
		if (curAnimation == BHA_RETIRE && dy>=0)
		{
			if (curFrame > 4)
			{
				vx = dRetire[indexDRetire].x - x;
				vy = dRetire[indexDRetire].y - y;
				indexDRetire = (indexDRetire + 1) % 3;

				fixV(vx, vy, 90);
			}
			else
			{
				vx = 0;
				vy = 0;
			}
		}
		else
			if (curAnimation == BHA_SHOT)
			{
				vx = 0;
				vy = 0;
			}
			else
				if (curAnimation == BHA_FLY_HALF && vx==0)
				{
					vx = direction * BLASTHORNET_FLY_VX;
					vy = BLASTHORNET_FLY_VY;
				}
				else
					if (curAnimation == BHA_FLY_FULL || curAnimation == BHA_SHOT_DIRECT)
					{
						direction = MEGAMAN->x - x >= 0 ? Right : Left;
						if (curAnimation == BHA_FLY_FULL && timeFlyFull.isTerminated())
						{
							changeAction(BHA_SHOT_DIRECT);
							timeShot.start();
							blockBullet = false;
						}
						else
							if (curAnimation == BHA_SHOT_DIRECT && timeShot.isTerminated())
							{
								if (!blockBullet)
								{
									ENEMYBULLET->_Add(new BlastHornet_Bullet(0, 0, true));
									blockBullet = true;
								}
								changeAction(BHA_FLY_FULL);
								timeFlyFull.start();
							}
						timeFlyFull.canCreateFrame();
						timeShot.canCreateFrame();
					}

	
}
void BlastHornet::updateBeforeHandle()
{
	if (!alive)
		return;

	isOnGround = false;
	if (curAnimation == BHA_FLY_FULL || curAnimation == BHA_SHOT_DIRECT )
	{
		if (indexFlyFull == -1)
		{
			dx = ptsFly[0].x - x;
			dy = ptsFly[0].y+(ptsFly[1].y-ptsFly[0].y)/2 - y;
			fixV(dx, dy, 0.85);
		}
	}
	else
	{
		if (curAnimation == BHA_FLY_HALF)
		{
			if (!(y <= 603 && dy < 0))
				vy += -185 * GAME_TIME->frameTime;
			else
				vy = 0;
		}

		dx = vx * GAME_TIME->frameTime;
		dy = vy * GAME_TIME->frameTime;
	}
	BaseObject::update();

	if (delayAnimation.canCreateFrame())
	{
		if (curAnimation != nextAnimation)
		{
			curAnimation = nextAnimation;
			curFrame = 0;
		}
		else
		{
			if (curAnimation == BHA_APPEAR)
			{
				if (curFrame < sprite->animates[curAnimation].nFrame - 1)
					curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
				timeAppear.canCreateFrame();
			}
			else
			{
				if (curFrame < sprite->animates[curAnimation].nFrame - 1)
					curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
			}

		}
	}
}
void BlastHornet::updateLocation()
{
	if (!alive)
		return;

	if ((curAnimation == BHA_FLY_FULL || curAnimation == BHA_SHOT_DIRECT) && indexFlyFull != -1)
	{
		if (indexFlyFull == 0)
		{
			x += 0.85;
			y = sin((ptsFly[1].x - x) / (ptsFly[1].x - ptsFly[0].x) * 2 * PI);
			if (-1 <= y && y <= 0)
			{
				y = -y * (ptsFly[1].y - (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2)) / 1 + (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2);
			}
			else
				if ((0 <= y && y <= 1))
				{
					y = ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2 - y * (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2 - ptsFly[0].y) / 1;
				}
		}
		else
		{
			x -= 0.85;
			y = sin((x - ptsFly[0].x) / (ptsFly[1].x - ptsFly[0].x) * 2 * PI);
			if (-1 <= y && y <= 0)
			{
				y = -y * (ptsFly[1].y - (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2)) / 1 + (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2);
			}
			else
				if ((0 <= y && y <= 1))
				{
					y = ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2 - y * (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2 - ptsFly[0].y) / 1;
				}
		}
	}
	else
	{
		x += dx;
		y += dy;
	}
}
void BlastHornet::draw()
{
	if (!alive)
	{
		if (timeDeath.isTerminated())
			return;
		else
			timeDeath.canCreateFrame();

		int xInViewport, yInViewport;
		Map::curMap->convertToViewportPos(xCenter(), yCenter(), xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, BHA_DEATH, 0, true);

		return;
	}

	MovableObject::draw();

	BLASTHORNET_WING->draw();
}
void BlastHornet::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);

	if (curAnimation == BHA_PRICK && other->collisionType == CT_GROUND && curFrame == sprite->animates[curAnimation].nFrame - 1)
	{
		if (ny == -1)
		{
			curAnimation = BHA_RETIRE;
			nextAnimation = BHA_RETIRE;
			curFrame = 0;

			direction = indexDRetire == 2 ? Left : Right;
		}
		else
			if (nx!=0)
			{
				if (MEGAMAN->x - x >= 0)
				{
					vx = MEGAMAN->right() - x;
					vy = MEGAMAN->y - y;
				}
				else
				{
					vx = MEGAMAN->x - x - width;
					vy = MEGAMAN->y - y;
				}
				direction = MEGAMAN->x - x >= 0 ? Right : Left;

				fixV(vx, vy, 90);
			}
	}
	else
		if (curAnimation == BHA_RETIRE && other->collisionType == CT_GROUND && (nx != 0 || ny == 1))
		{
			curAnimation = BHA_SHOT;
			nextAnimation = BHA_SHOT;
			curFrame = 0;
			timeShot.start();

			direction = direction == Left ? Right : Left;
		}
		else
			if (curAnimation == BHA_FLY_HALF && other->collisionType == CT_GROUND && nx != 0)
			{
				if (life >= BLASTHORNET_LIFE / 2)
				{
					curAnimation = BHA_PRICK;
					nextAnimation = BHA_PRICK;
					curFrame = 0;

					direction = direction == Left ? Right : Left;
				}
				else
				{
					changeAction(BHA_FLY_FULL);
					indexFlyFull = -1;
					timeFlyFull.start();
					direction = MEGAMAN->x - x >= 0 ? Right : Left;
				}
			}
}
void BlastHornet::onAABBCheck(BaseObject * other)
{
	Enemy::onAABBCheck(other);
}
void BlastHornet::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	direction = Left;
	timeAppear.start();
	timeShot.init(0.09, 10);
	timeFlyFull.init(0.3, 10);

	indexDRetire = 0;
	indexFlyFull = -1;
	blockBullet = false;
	life = BLASTHORNET_LIFE;

	BLASTHORNET_WING->release();
}

void BlastHornet::fixV(float & vx, float & vy, float v)
{
	if (abs(vx) > v)
	{
		vy = v * vy / abs(vx);
		vx = vx > 0 ? v : -v;
	}
	if (abs(vy) > v)
	{
		vx = v * vx / abs(vy);
		vy = vy > 0 ? v : -v;
	}

	if (abs(vx) < 10)
	{
		vx = vx * v / abs(vy);
		vy = vy > 0 ? v : -v;
	}
	if (abs(vy) < 10)
	{
		vy = vy * v / abs(vx);
		vx = vx > 0 ? v : -v;
	}
}

void BlastHornet::release()
{
	delete instance;
	instance = 0;

	BLASTHORNET_WING->release();
}

BlastHornet::BlastHornet()
{
	sprite = SPRITEMANAGER->sprites[SPR_BLASTHORNET];
	damage = BLASTHORNET_DAMAGE;
	life = BLASTHORNET_LIFE;
	alive = true;
	
	x = 4530;
	y = 628;
	width = 40;
	height = 72;
	
	timeAppear.init(0.25, 10);
	timeAppear.start();
	timeShot.init(0.09, 10);
	timeFlyFull.init(0.3, 10);


	dRetire[0].x = 4530;
	dRetire[0].y = 623;
	dRetire[1].x = 4530;
	dRetire[1].y = 623;
	dRetire[2].x = 4356;
	dRetire[2].y = 623;
	indexDRetire = 0;

	ptsFly[0].x = 4368;
	ptsFly[0].y = 617;
	ptsFly[1].x = 4526;
	ptsFly[1].y = 680;
	indexFlyFull = -1;

	blockBullet = false;
}

BlastHornet::~BlastHornet()
{
}
