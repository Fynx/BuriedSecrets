/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/Animator.hpp"


Animator::Animator(Mind *mind) : mind(mind)
{}

Animator::~Animator()
{}

void Animator::addObject(Object *obj)
{
	objects.push_back(obj);
}

void Animator::removeObject(Object *obj)
{
	if (objects.contains(obj))
		objects.remove(objects.indexOf(obj));
}

bool Animator::hasObject(Object *obj)
{
	return objects.contains(obj);
}

bool Animator::hasObject(const Object *obj) const
{
	for (auto &o : objects)
		if (o == obj)
			return true;
	return false;
}
