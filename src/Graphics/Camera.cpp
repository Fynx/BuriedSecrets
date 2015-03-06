/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Camera.hpp"

#include "Common/Geometry.hpp"


Camera::Camera(const PhysicsEngine *physicsEngine, const Viewport *viewport)
	: physicsEngine{physicsEngine}, viewport{viewport}
{}


QList<const Object *> Camera::getVisibleObjects() const
{
	return physicsEngine->getObjectsInRect(BS::Geometry::scaleRect(viewport->getCurrentView(), 2.0f));
}


int Camera::discretizeAngle(const float angle, const int range) const
{
	int res = static_cast<int>(round((angle + 90.0f) * range / 360.0f)) % range;
	if (res < 0) {
		res += range;
	}
	return res;
}


const Perspective *Camera::getPerspective() const
{
	return viewport->getPerspective();
}


const Viewport *Camera::getViewport() const
{
	return viewport;
}


sf::View Camera::getCurrentView() const
{
	const Perspective *perspective = viewport->getPerspective();
	QRectF currentViewInPx = perspective->fromMetresToPixels(viewport->getCurrentView());
	return sf::View(sf::FloatRect(
			currentViewInPx.left(), currentViewInPx.top(),
			currentViewInPx.width(), currentViewInPx.height()));
}
