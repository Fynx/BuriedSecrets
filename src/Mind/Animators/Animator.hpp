/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtCore>

#include "GameObjects/Object.hpp"

class Mind;

/**
 * @class Animator
 * Abstract class that represents periodic actions.
 * Animators iterate over Objects and check and modify their states.
 * Each Animator has a list of Objects attached.
 */
class Animator {
public:
	Animator(Mind *);
	virtual ~Animator();

	/** Standard interface for every Animator. */
	virtual void act() = 0;
	void addObject(Object *obj);
	void removeObject(Object *obj);
	bool hasObject(Object *obj);
	bool hasObject(const Object *obj) const;

protected:
	QVector<Object *> objects;
	Mind *mind;
};
