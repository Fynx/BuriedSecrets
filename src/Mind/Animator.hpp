#pragma once

#include "GameObjects/Object.hpp"

#include <QtCore>

class Animator {
public:
	virtual ~Animator();

	virtual void act() = 0;

protected:
	//TODO access with protected function to a private vector would be nice
	QVector <Object *> objects;
};