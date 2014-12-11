/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

#include <QtCore>

class Mind;

class Animator {
public:
	Animator(Mind *);
	virtual ~Animator();

	virtual void act() = 0;
	virtual void addObject(Object *obj);
	virtual void removeObject(Object *obj);
	bool hasObject(Object *obj);

protected:
	QVector <Object *> objects;
	Mind *mind;
};
