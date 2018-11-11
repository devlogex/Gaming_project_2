#include "Camera.h"
#include "Megaman.h"
#include "Constant.h"

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
	if ((MEGAMAN->x + MEGAMAN->dx < xCenter() && MEGAMAN->dx < 0) || (MEGAMAN->x + MEGAMAN->dx > xCenter() && MEGAMAN->dx > 0))
		dx = MEGAMAN->dx;
	else
		dx = 0;
	if ((MEGAMAN->y + MEGAMAN->dy < yCenter() && MEGAMAN->dy < 0) || (MEGAMAN->y + MEGAMAN->dy > yCenter() && MEGAMAN->dy > 0))
		dy = MEGAMAN->dy;
	else
		dy = 0;
}
Camera::Camera()
{
}

Camera::~Camera()
{
}
