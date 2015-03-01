/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicalEntityFactory.hpp"

#include "Common/Strings.hpp"
#include "Graphics/AnimatedGraphicalEntity.hpp"
#include "Graphics/AnimationSet.hpp"
#include "Graphics/ShotEffectGraphicalEntity.hpp"
#include "Graphics/StaticGraphicalEntity.hpp"


GraphicalEntityFactory::GraphicalEntityFactory(GraphicsDataManager *graphicsDataManager, const Viewport *viewport)
	: graphicalEffectFactory{viewport}, graphicsDataManager{graphicsDataManager}, viewport{viewport}
{}


GraphicalEntityFactory::~GraphicalEntityFactory()
{
	deleteObjects();
}


GraphicalEntity* GraphicalEntityFactory::get(const Object* object) const
{
	auto iter = objectEntities.find(object);

	if (iter != objectEntities.end()) {
		return iter.value();
	}

	return nullptr;
}


GraphicalEntity* GraphicalEntityFactory::get(Object* object) const
{
	return get(static_cast<const Object*>(object));
}


GraphicalEntity *GraphicalEntityFactory::getOrCreate(const Object *object)
{
	auto iter = objectEntities.find(object);
	GraphicalEntity *ptr = nullptr;

	if (iter == objectEntities.end()) {
		auto objectType = object->getPrototype()->getProperty("type").toString();
		QList<QPointF> basePolygon;

		if (objectType == "unit") {
			// Build an AnimationSet object and pass it to the AnimatedGraphicalEntity
			AnimationSet::SetType s;
			const auto animationsList = object->getPrototype()->getAnimationsData();
			for (const auto& anim: animationsList) {
				s[anim->getState()] = graphicsDataManager->getAnimation(anim->getName());
				qDebug() << anim->getName() << " for " << anim->getState();
			}

			// Get centre, radius and build a polygon emulating circle.
			const float radius = object->getPrototype()->getProperty("baseRadius").toFloat();
			QPointF centre = object->getPrototype()->getBaseCentre();
			// Clockwise
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x() - radius, centre.y()}));
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x(), centre.y() - radius}));
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x() + radius, centre.y()}));
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x(), centre.y() + radius}));

			ptr = new AnimatedGraphicalEntity(object, basePolygon, &graphicalEffectFactory, AnimationSet{s});
		} else if (objectType == "location") {
			// Convert base polygon from metres to pixels.
			basePolygon = object->getPrototype()->getBasePolygon();
			for (QPointF &p: basePolygon) {
				p = viewport->fromMetresToPixels(p);
			}

			ptr = new StaticGraphicalEntity(object, basePolygon, &graphicalEffectFactory,
					graphicsDataManager->getTexture(
							object->getPrototype()->getProperty("textureName").toString()));
		} else {
			qDebug() << "FAIL!";
			Q_ASSERT(false);	// Not a known type.
		}

		Q_ASSERT(ptr != nullptr);
		objectEntities[object] = ptr;
	} else {
		ptr = iter.value();
	}

	return ptr;
}


GraphicalEntity *GraphicalEntityFactory::getOrCreate(Object *object)
{
	return getOrCreate(static_cast<const Object*>(object));
}


EffectGraphicalEntity *GraphicalEntityFactory::getOrCreateEffectEntity(const Effect &effect)
{
	auto iter = effectEntities.find(effect.getEffectData());
	EffectGraphicalEntity *ptr = nullptr;

	if (iter == effectEntities.end()) {
		QString name = effect.getName();
		if (name == Effects::Shot) {
			ptr = new ShotEffectGraphicalEntity{viewport};
		}

		if (!ptr) {
			warn("Unknown EffectEntity type! Effect name: " + effect.getName());
			return ptr;
		}
		effectEntities[effect.getEffectData()] = ptr;
	} else {
		ptr = iter.value();
	}

	// Reusing objects for new pointers.
	ptr->updateData(effect.getEffectData());

	return ptr;
}


void GraphicalEntityFactory::deleteObjects()
{
	// Free the GraphicalObjects.
	qDeleteAll(objectEntities);
	qDeleteAll(effectEntities);
}



