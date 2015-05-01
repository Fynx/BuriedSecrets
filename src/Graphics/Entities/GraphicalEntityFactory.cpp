/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Entities/GraphicalEntityFactory.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Environment.hpp"
#include "GameObjects/Object.hpp"
#include "GameObjects/Unit.hpp"
#include "Graphics/GraphicsDataManager.hpp"
#include "Graphics/Entities/EnvironmentGraphicalEntity.hpp"
#include "Graphics/Entities/LocationGraphicalEntity.hpp"
#include "Graphics/Entities/MissEffectGraphicalEntity.hpp"
#include "Graphics/Entities/MoveCommandEffectGraphicalEntity.hpp"
#include "Graphics/Entities/ShotEffectGraphicalEntity.hpp"
#include "Graphics/Entities/StaticGraphicalEntity.hpp"
#include "Graphics/Entities/UnitGraphicalEntity.hpp"
#include "Mind/Effect.hpp"
#include "UserInterface/Viewport/Viewport.hpp"


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
		const Prototype *prototype = object->getPrototype();
		auto objectType = prototype->getProperty("type").toString();
		QList<QPointF> basePolygon;

		if (objectType == "unit") {
			// Get centre, radius and build a polygon emulating circle.
			const float radius = prototype->getProperty("baseRadius").toFloat();
			QPointF centre = prototype->getBaseCentre();
			// Clockwise
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x() - radius, centre.y()}));
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x(), centre.y() - radius}));
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x() + radius, centre.y()}));
			basePolygon.append(viewport->fromMetresToPixels(QPointF{centre.x(), centre.y() + radius}));

			// New textures.
			const GraphicalTextureSet *textureSet = graphicsDataManager->getTextureSet(
					prototype->getProperty(Data::TextureSet).toString());
			const Unit *unit = dynamic_cast<const Unit *>(object);
			assert(unit != nullptr);	// If this fails, then something is REALLY messed up.
			ptr = new UnitGraphicalEntity{unit, basePolygon, &graphicalEffectFactory, textureSet};
		} else if (objectType == "location" || objectType == "environment") {
			// Convert base polygon from metres to pixels.
			basePolygon = prototype->getBasePolygon();
			for (QPointF &p: basePolygon) {
				p = viewport->fromMetresToPixels(p);
			}

			if (objectType == "location") {
				const Location *location = dynamic_cast<const Location *>(object);
				assert(location != nullptr);

				ptr = new LocationGraphicalEntity{location, basePolygon, &graphicalEffectFactory,
						graphicsDataManager->getTextureSet(
								prototype->getProperty(Data::TextureSet).toString())};
			} else {
				const Environment *environmentObject = dynamic_cast<const Environment *>(object);
				assert(environmentObject != nullptr);

				ptr = new EnvironmentGraphicalEntity(environmentObject, basePolygon,
						&graphicalEffectFactory,
						environmentObject->isTransparent() ? nullptr :
								graphicsDataManager->getTextureSet(
										prototype->getProperty(Data::TextureSet
												).toString()));
			}
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
					graphicsDataManager->getTextureSet(Resources::ArrowDownCursor)->getFrame(
							ImageMetaData{BS::State::Idle, BS::ItemType::Invalid,
								      BS::Graphic::Direction::Invalid, 0}
					)};
		} else if (name == Effects::Miss) {
			ptr = new MissGraphicalEntity{viewport,
						      graphicsDataManager->getTextureSet(Resources::MissTextureSet)};
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
