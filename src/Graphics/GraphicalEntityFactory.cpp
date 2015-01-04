/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicalEntityFactory.hpp"

#include "Graphics/AnimatedGraphicalEntity.hpp"
#include "Graphics/AnimationSet.hpp"
#include "Graphics/StaticGraphicalEntity.hpp"


GraphicalEntityFactory::GraphicalEntityFactory(GraphicsDataManager *graphicsDataManager, const Perspective *perspective)
	: graphicsDataManager{graphicsDataManager}, perspective{perspective}
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
			const QVariantList centre = object->getPrototype()->getProperty("baseCentre").toList();
			const float centreX = centre[0].toFloat();
			const float centreY = centre[1].toFloat();

			// Clockwise
			basePolygon.append(perspective->getTranslatedPoint(QPointF{centreX - radius, centreY}));
			basePolygon.append(perspective->getTranslatedPoint(QPointF{centreX, centreY - radius}));
			basePolygon.append(perspective->getTranslatedPoint(QPointF{centreX + radius, centreY}));
			basePolygon.append(perspective->getTranslatedPoint(QPointF{centreX, centreY + radius}));

			ptr = new AnimatedGraphicalEntity(object, basePolygon, AnimationSet{s});
		} else if (objectType == "building") {
			// Convert basePolygon from prototype to a QList<QPointF>
			const QVariantList polygon = object->getPrototype()->getProperty("basePolygon").toList();
			for (const QVariant &p: polygon) {
				const QVariantList &point = p.toList();
				basePolygon.append(perspective->getTranslatedPoint(
						QPointF{point[0].toFloat(), point[1].toFloat()}));
			}

			ptr = new StaticGraphicalEntity(object, basePolygon, graphicsDataManager->getTexture(
					object->getPrototype()->getProperty("textureName").toString()));
		} else {
			qDebug() << "FAIL!";
			Q_ASSERT(false);	// Not a known type.
		}

		Q_ASSERT(ptr != nullptr);
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



