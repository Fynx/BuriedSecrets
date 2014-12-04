/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicalEntityFactory.hpp"

#include "Graphics/StaticGraphicalEntity.hpp"


GraphicalEntityFactory::GraphicalEntityFactory(GraphicsDataManager *graphicsDataManager)
: graphicsDataManager{graphicsDataManager}
{}


GraphicalEntityFactory::~GraphicalEntityFactory()
{
	deleteObjects();
}


GraphicalEntity* GraphicalEntityFactory::get(const Object* object)
{
	auto iter = map.find(object);
	GraphicalEntity *ptr = nullptr;
	if (iter == map.end()) {
		ptr = new StaticGraphicalEntity(object, graphicsDataManager->getTexture("Soszu"));
		map[object] = ptr;
	} else {
		ptr = iter.value();
	}

	return ptr;
}


GraphicalEntity* GraphicalEntityFactory::get(Object* object)
{
	return get(static_cast<const Object*>(object));
}


void GraphicalEntityFactory::deleteObjects()
{
	// Free the GraphicalObjects.
	qDeleteAll(map);
}


