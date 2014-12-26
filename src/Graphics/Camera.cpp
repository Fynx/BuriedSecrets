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
	return static_cast<int>(round(angle * range / 360.0f)) % range;
}

