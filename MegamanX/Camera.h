#pragma once
#include "BaseObject.h"
#include "CollisionManager.h"
#include "ObjectsCategory.h"

class Camera : public BaseObject
{
	static Camera* instance;
public:
	static Camera* getInstance();

	ObjectsCategory objectsInCamera;

	void update();
	void onCollision(BaseObject* other, int nx, int ny);

	Camera();
	~Camera();
};
