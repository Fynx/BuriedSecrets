/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

#include <QtCore>

class Animator {
public:
	virtual ~Animator();

	virtual void act() = 0;
	void addObject(Object *obj);
	void removeObject(Object *obj);
	bool hasObject(Object *obj);

protected:
	QVector <Object *> objects;
};
