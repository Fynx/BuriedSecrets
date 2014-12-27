/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Camera.hpp"

Camera::Camera(const PhysicsEngine *physicsEngine, const Viewport *viewport)
	: physicsEngine{physicsEngine}, viewport{viewport}
{}


QList<const Object *> Camera::getVisibleObjects() const
{
	return physicsEngine->getObjectsInRect(viewport->getCurrentView());
}


int Camera::discretizeAngle(const float angle, const int range) const
{
	int res = static_cast<int>(round(angle * range / 360.0f)) % range;
	if (res < 0) {
		res += range;
	}
	return res;
}


const Perspective *Camera::getPerspective() const
{
	return viewport->getPerspective();
}

