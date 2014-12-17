/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicalEntityFactory.hpp"

#include "Graphics/AnimatedGraphicalEntity.hpp"
#include "Graphics/AnimationSet.hpp"
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
		// Build an AnimationSet object and pass it to the AnimatedGraphicalEntity
		AnimationSet::SetType s;
		const auto animationsList = object->getPrototype()->getAnimationsData();
		for (const auto& anim: animationsList) {
			s[anim->getState()] = graphicsDataManager->getAnimation(anim->getName());
			qDebug() << anim->getName() << " for " << anim->getState();
		}
		ptr = new AnimatedGraphicalEntity(object, AnimationSet{s});
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


