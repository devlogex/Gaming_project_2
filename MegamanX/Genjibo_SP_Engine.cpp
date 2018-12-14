#include "Genjibo_SP_Engine.h"
#include"Genjibo_SP.h"
#include"Genjibo_SP_Engine_Location.h"
#include"Map.h"
#include"Genjibo.h"


Genjibo_SP_Engine*Genjibo_SP_Engine::instance = 0;
Genjibo_SP_Engine * Genjibo_SP_Engine::getInstance()
{
	if (instance == 0)
		instance = new Genjibo_SP_Engine();
	return instance;
}
void Genjibo_SP_Engine::update()
{
	if (GENJIBO_SP->curAnimation == GSA_FLY)
	{
		if (curAnimation != GSEA_FLY)
			curAnimation = GSEA_FLY;
	}
	else
		if (GENJIBO_SP->curAnimation == GSA_SHOT)
		{
			if (curAnimation != GSA_SHOT)
				curAnimation = GSA_SHOT;
			else
			{
				if (GENJIBO_SP->timeShot.curLoop >= GENJIBO_SP->timeShot.loopCount / 1.3)
				{
					GENJIBO->timeAppear.start();
				}
			}
		}
	curFrame = (curFrame + 1) % sprite->animates[curAnimation].nFrame;

}
void Genjibo_SP_Engine::draw()
{
	int x1, x2, y1, y2;
	int x3 = 0, y3 = 0;
	if (curAnimation == GSEA_FLY)
	{
		x1 = GENJIBO_SP_ENGINE_LOCATION->ptsFly[curFrame][0].x + GENJIBO_SP->x;
		x2 = GENJIBO_SP_ENGINE_LOCATION->ptsFly[curFrame][1].x + GENJIBO_SP->x;
		y1 = GENJIBO_SP_ENGINE_LOCATION->ptsFly[curFrame][1].y + GENJIBO_SP->y;
		y2 = y1;
	}
	else
		if (curAnimation == GSEA_SHOT)
		{
			x1 = GENJIBO_SP_ENGINE_LOCATION->ptsShot[curFrame][0].x + GENJIBO_SP->x;
			x2 = GENJIBO_SP_ENGINE_LOCATION->ptsShot[curFrame][1].x + GENJIBO_SP->x;
			y1 = GENJIBO_SP_ENGINE_LOCATION->ptsShot[curFrame][1].y + GENJIBO_SP->y;
			y2 = y1;

			if (GENJIBO_SP->timeShot.curLoop >= GENJIBO_SP->timeShot.loopCount / 2)
			{
				x3 = GENJIBO_SP_ENGINE_LOCATION->ptsAppear[0].x + GENJIBO_SP->x;
				y3 = GENJIBO_SP_ENGINE_LOCATION->ptsAppear[0].y + GENJIBO_SP->y;
			}
		}

	int x2InViewport, y2InViewport;
	Map::curMap->convertToViewportPos(x2, y2, x2InViewport, y2InViewport);

	sprite->draw(x2InViewport, y2InViewport, curAnimation, curFrame);



	int x1InViewport, y1InViewport;
	Map::curMap->convertToViewportPos(x1, y1, x1InViewport, y1InViewport);

	int trucQuay = x1InViewport + sprite->animates[curAnimation].frames[curFrame].width / 2;
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}
	sprite->draw(x1InViewport, y1InViewport, curAnimation, curFrame);
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}


	if (x3 != 0)
	{
		int x3InViewport, y3InViewport;
		Map::curMap->convertToViewportPos(x3, y3, x3InViewport, y3InViewport);

		sprite->draw(x3InViewport, y3InViewport, 2, 0);
	}
}

void Genjibo_SP_Engine::restore(BaseObject * obj)
{
}
void Genjibo_SP_Engine::release()
{
	delete instance;
	instance = 0;
}
Genjibo_SP_Engine::Genjibo_SP_Engine()
{
	sprite = SPRITEMANAGER->sprites[SPR_GENJIBO_SP_ENGINE];
	GENJIBO_SP;
}

Genjibo_SP_Engine::~Genjibo_SP_Engine()
{
}
