#include "Genjibo.h"
#include"Map.h"

Genjibo*Genjibo::instance = 0;
Genjibo * Genjibo::getInstance()
{
	if (instance == 0)
		instance = new Genjibo();
	return instance;
}

void Genjibo::update()
{
	updateV();
	updateAnimation();
	updateBeforeHandle();
}

void Genjibo::updateAnimation()
{
	if (curAnimation == GA_APPEAR && timeAppear.isTerminated() && curFrame == sprite->animates[GA_APPEAR].nFrame - 1)
	{
		changeAction(GA_ROLL_RUN);

		timeRollStand.start();
		curAnimation = GA_ROLL_STAND;
	}
	else
		if (curAnimation == GA_ROTARY_STAND && timeRotaryStand.isTerminated() && curFrame == 0)
		{
			changeAction(GA_ROTARY_RUN);
			timeRotaryRun.start();
		}
}

void Genjibo::updateV()
{
	if (curAnimation == GA_ROLL_RUN || curAnimation== GA_ROTARY_RUN)
		vx = direction * GENJIBO_VX;

}

void Genjibo::updateBeforeHandle()
{
	if (!alive)
		return;

	isOnGround = false;
	if (curAnimation != GA_RUN)
		updateVelocity();
	BaseObject::update();

	if (delayAnimation.canCreateFrame())
	{
		if (curAnimation != nextAnimation && curAnimation == GA_ROLL_STAND && timeRollStand.isTerminated())
		{
			curAnimation = nextAnimation;
			if (nextAnimation == GA_ROLL_RUN)
				timeRollRun.start();
			else
				if (nextAnimation == GA_RUN)
				{
					indexRun = 0;
					dx = dRun[indexRun].x*GENJIBO_DX;
					dy = dRun[indexRun].y*GENJIBO_DY;
					curFrame = 0;
				}
				else
					if (nextAnimation == GA_ROTARY_STAND)
					{
						curFrame = 0;
						timeRotaryStand.start();
					}
		}
		else
			if (curAnimation != nextAnimation && curAnimation != GA_ROLL_STAND)
			{
				curAnimation = nextAnimation;
				curFrame = 0;
			}
			else
			{
				if (curAnimation == GA_APPEAR && !timeAppear.isTerminated())
				{
					if (curFrame < sprite->animates[curAnimation].nFrame - 1)
						curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
					timeAppear.canCreateFrame();
				}
				else
					if (curAnimation == GA_ROLL_STAND && !timeRollStand.isTerminated())
					{
						curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
						timeRollStand.canCreateFrame();
					}
					else
						if (curAnimation == GA_ROLL_RUN)
						{
							curFrame = direction==Left?(curFrame + 1) % sprite->animates[curAnimation].nFrame: (curFrame - 1+ sprite->animates[curAnimation].nFrame) % sprite->animates[curAnimation].nFrame;
							timeRollRun.canCreateFrame();
						}
						else
							if (curAnimation == GA_ROTARY_STAND && (!timeRotaryStand.isTerminated()|| curFrame!=0))
							{
								curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
								timeRotaryStand.canCreateFrame();
							}
							else
								if (curAnimation == GA_ROTARY_RUN && (!timeRotaryRun.isTerminated() || curFrame != 0 || nextAnimation==GA_ROTARY_RUN))
								{
									curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;
									timeRotaryRun.canCreateFrame();
								}
			}
	}
}

void Genjibo::draw()
{
	if (!alive)
	{
		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_DELETEOBJECT];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 6;
		}

		if (timeDeath.isTerminated())
			return;
	}

	if (timeDamaged.canCreateFrame())
		drawDamaged = !drawDamaged;
	else
		drawDamaged = false;

	if (drawDamaged)
	{
		int xInViewport, yInViewport;
		Map::curMap->convertToViewportPos(xCenter(), yCenter(), xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, GA_DAMAGED, 0, true);
	}
	else
	{
		int xInViewport, yInViewport;
		Map::curMap->convertToViewportPos(xCenter(), yCenter(), xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame, true);
	}
}

void Genjibo::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);

	if (other->collisionType == CT_GROUND && nx != 0)
	{
		direction = (Direction)nx;

		if (curAnimation == GA_ROLL_RUN && timeRollRun.isTerminated() && nx == -1)
		{
			changeAction(GA_RUN);

			curAnimation = GA_ROLL_STAND;
			timeRollStand.start();
		}
		
		if (curAnimation == GA_ROTARY_RUN && timeRotaryRun.isTerminated() && nx == -1)
		{
			changeAction(GA_ROLL_RUN);

			curAnimation = GA_ROLL_STAND;
			timeRollStand.start();
		}
	}

	if (other->collisionType == CT_GROUND && curAnimation == GA_RUN)
	{
		if (indexRun == 0 && nx == 1)
		{
			indexRun++;
			dx = dRun[indexRun].x*GENJIBO_DX;
			dy = dRun[indexRun].y*GENJIBO_DY;
		}
		else
			if (indexRun == 1 && ny == 1)
			{
				indexRun++;
				dx = dRun[indexRun].x*GENJIBO_DX;
				dy = dRun[indexRun].y*GENJIBO_DY;
			}
			else
				if (indexRun == 2 && nx == -1)
				{
					indexRun++;
					dx = dRun[indexRun].x*GENJIBO_DX;
					dy = dRun[indexRun].y*GENJIBO_DY;
				}
				else
					if (indexRun == 3 && ny == -1)
					{
						indexRun = -1;
						changeAction(GA_ROTARY_STAND);

						curAnimation = GA_ROLL_STAND;
						timeRollStand.start();
					}
	}
}

void Genjibo::onAABBCheck(BaseObject * other)
{
	if (other->collisionType == CT_WEAPON)
		timeDamaged.start();
}

void Genjibo::restore(BaseObject * obj)
{
	Enemy::restore(obj);
	life = BOSS_LIFE;
	direction = Left;
	indexRun = -1;
	timeAppear.init(0.23, 10);
	timeRollStand.init(0.3, 10);
	timeRollRun.init(0.7, 20);
	timeRotaryStand.init(0.4, 10);
	timeRotaryRun.init(0.5, 10);
	timeDamaged.init(0.2, 10);
	drawDamaged = false;
}

Genjibo::Genjibo()
{
	sprite = SPRITEMANAGER->sprites[SPR_GENJIBO];
	damage = GENJIBO_DAMAGE;
	life = GENJIBO_LIFE;
	alive = true;
	width = 47;
	height = 47;

	delayAnimation.minFrameTime = 0.012f;
	delayAnimation.maxFrameTime = 0.015f;

	timeAppear.init(0.23, 10);
	timeRollStand.init(0.3, 10);
	timeRollRun.init(0.7, 20);
	timeRotaryStand.init(0.4, 10);
	timeRotaryRun.init(0.5, 10);
	timeDamaged.init(0.2, 10);
	drawDamaged = false;

	indexRun = -1;
	dRun[0].x = -1;
	dRun[0].y = 0;
	dRun[1].x = 0;
	dRun[1].y = -1;
	dRun[2].x = 1;
	dRun[2].y = 0;
	dRun[3].x = 0;
	dRun[3].y = 1;
}

Genjibo::~Genjibo()
{
}
