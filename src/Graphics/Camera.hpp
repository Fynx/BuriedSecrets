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


class Camera {
public:
	Camera(const PhysicsEngine *physicsEngine, const Viewport *viewport);

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