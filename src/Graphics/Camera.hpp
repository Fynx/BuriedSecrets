/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

class Viewport;
class Object;
class Perspective;
class PhysicsEngine;
template<class T>
class QList;

namespace sf {
	class View;
};


/**
 * @brief This class provides utility methods for Graphics to query physics for visible objects and to access all
 * geometry-related functionality.
 */
class Camera {
public:
	Camera(const PhysicsEngine *physicsEngine, const Viewport *viewport);

	/**
	 * @brief Returns a list of objects currently visible (based on current state of Viewport).
	 */
	QList<const Object *> getVisibleObjects() const;
	/**
	 * @brief This method transforms a continuous angle into a discretized form.
	 */
	int discretizeAngle(const float angle, const int range = 8) const;
	const Perspective *getPerspective() const;
	const Viewport *getViewport() const;
	sf::View getCurrentView() const;

private:
	const PhysicsEngine *physicsEngine;
	const Viewport *viewport;
};
