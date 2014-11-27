#include "Graphics/GraphicalObjectFactory.hpp"


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
		ptr = new GraphicalObject(object);
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
	for (const auto& elem: map) {
		delete elem;
	}
}


