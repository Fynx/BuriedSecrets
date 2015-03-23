/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Entities/GraphicalEntityFactory.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "Graphics/Entities/MoveCommandEffectGraphicalEntity.hpp"
#include "Graphics/Entities/ShotEffectGraphicalEntity.hpp"
#include "Graphics/Entities/StaticGraphicalEntity.hpp"
#include "Graphics/Entities/UnitGraphicalEntity.hpp"


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
			// Get centre, radius and build a polygon emulating circle.
			const float radius = object->getPrototype()->getProperty("baseRadius").toFloat();
			QPointF centre = object->getPrototype()->getBaseCentre();
			// Clockwise
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x() - radius, centre.y()}));
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x(), centre.y() - radius}));
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x() + radius, centre.y()}));
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x(), centre.y() + radius}));

			// New textures.
			const GraphicalTextureSet *textureSet = graphicsDataManager->getTextureSet(
					object->getPrototype()->getProperty(Data::TextureSet).toString());
			const Unit *unit = dynamic_cast<const Unit *>(object);
			assert(unit != nullptr);	// If this fails, then something is REALLY messed up.
			ptr = new UnitGraphicalEntity{unit, basePolygon, &graphicalEffectFactory, textureSet};
		} else if (objectType == "location" || objectType == "environment") {
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
		} else if (name == Effects::MoveCommand) {
			ptr = new MoveCommandEffectGraphicalEntity{viewport,
					graphicsDataManager->getTexture(Resources::ArrowDownCursor)};
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



