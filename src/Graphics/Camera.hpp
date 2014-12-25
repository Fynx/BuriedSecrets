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

private:
	const PhysicsEngine *physicsEngine;
	const Viewport *viewport;
};