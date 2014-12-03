#include "Graphics/GraphicalObjectFactory.hpp"

#include "Graphics/StaticGraphicalObject.hpp"


GraphicalObjectFactory::GraphicalObjectFactory()
{

}


GraphicalObjectFactory::~GraphicalObjectFactory()
{
	deleteObjects();
}


GraphicalObject* GraphicalObjectFactory::get(const Object* object)
{
	auto iter = map.find(object);
	GraphicalObject *ptr = nullptr;
	if (iter == map.end()) {
		ptr = new StaticGraphicalObject(object);
		map[object] = ptr;
	} else {
		ptr = iter.value();
	}

	return ptr;
}


GraphicalObject* GraphicalObjectFactory::get(Object* object)
{
	return get(static_cast<const Object*>(object));
}


void GraphicalObjectFactory::deleteObjects()
{
	// Free the GraphicalObjects.
	qDeleteAll(map);
}


