#include "Camera.h"
#include "Megaman.h"
#include "Constant.h"
#include "Stage.h"
#include"GameTime.h"

Camera* Camera::instance = 0;
Camera* Camera::getInstance()
{
	if (instance == 0)
		instance = new Camera();
	return instance;
}

void Camera::onCollision(BaseObject* other, int nx, int ny)
{
	if (other->collisionType == CT_PREVENTMOVECAMERA)
		COLLISION->preventMove(this, other);
}

void Camera::update()
{
	if (Stage::updating)
	{
		if (Stage::curStage->xPre - CAMERA->x > 0)
			dx = (Stage::curStage->xPre - CAMERA->x)*GAME_TIME->frameTime;
		else
			dx = 1;
		if (Stage::curStage->yPre - CAMERA->y > 0)
			dy = (Stage::curStage->yPre - CAMERA->y)*GAME_TIME->frameTime*10;
		else
			dy = 0;
		return;
	}

	if ((MEGAMAN->x + MEGAMAN->dx < xCenter() && MEGAMAN->dx < 0) || (MEGAMAN->x + MEGAMAN->dx > xCenter() && MEGAMAN->dx > 0))
		dx = MEGAMAN->dx;
	else
		dx = 0;
	if ((MEGAMAN->y + MEGAMAN->dy < yCenter() && MEGAMAN->dy < 0) || (MEGAMAN->y + MEGAMAN->dy > yCenter() + VIEWPORT_HEIGHT / 4 && MEGAMAN->dy > 0))
		dy = MEGAMAN->dy;
	else
		dy = 0;

	if (x + dx < Stage::curStage->left() && dx < 0)
		dx = 0;
	if (right() + dx > Stage::curStage->right() && dx > 0)
		dx = 0;
	if (y + dy < Stage::curStage->top() && dy < 0)
		dy = 0;
	if (bottom() + dy > Stage::curStage->bottom() && dy > 0)
		dy = 0;
}
Camera::Camera()
{
}

Camera::~Camera()
{
}
