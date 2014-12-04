/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicalObjectFactory.hpp"

#include "Graphics/StaticGraphicalObject.hpp"


GraphicalObjectFactory::GraphicalObjectFactory(GraphicsDataManager *graphicsDataManager)
: graphicsDataManager{graphicsDataManager}
{}


GraphicalObjectFactory::~GraphicalObjectFactory()
{
	deleteObjects();
}


GraphicalObject* GraphicalObjectFactory::get(const Object* object)
{
	auto iter = map.find(object);
	GraphicalObject *ptr = nullptr;
	if (iter == map.end()) {
		ptr = new StaticGraphicalObject(object, graphicsDataManager->getTexture("Soszu"));
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


