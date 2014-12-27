/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "GameObjects/Object.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "UserInterface/Viewport.hpp"


class Camera {
public:
	Camera(const PhysicsEngine *physicsEngine, const Viewport *viewport);

	QList< const Object * > getVisibleObjects() const;
	/**
	 * @brief This method transforms a continuous angle into a discretized form.
	 */
	int discretizeAngle(const float angle, const int range = 8) const;
	const Perspective *getPerspective() const;

private:
	const PhysicsEngine *physicsEngine;
	const Viewport *viewport;
};