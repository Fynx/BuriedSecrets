/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Animator.hpp"


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
	if (objects.contains(obj)){
		objects.remove(objects.indexOf(obj));
	}
}


bool Animator::hasObject(Object *obj)
{
	return objects.contains(obj);
}
