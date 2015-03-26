/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Effects/AntipsychosisEffect.hpp"

#include "Common/Enums.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Location.hpp"
#include "Graphics/Entities/GraphicalEntity.hpp"


AntipsychosisEffect::AntipsychosisEffect(const Viewport *viewport)
		: CircleEffect{viewport, sf::Color{181, 20, 125, 90}, sf::Color{181, 20, 125, 35}}
{}


int AntipsychosisEffect::getOrderId() const
{
	return BS::Graphic::EffectOrder::Antipsychosis;
}


void AntipsychosisEffect::update(const GraphicalEntity *graphicalEntity)
{
	const Location *location = dynamic_cast<const Location *>(graphicalEntity->getObject());
	if (location == nullptr) {
		err("Cannot cast object to location for Antipsychosis Effect!");
		Q_ASSERT(false);
	}

	float radius = 25; // location->getRange();  FIXME PLOX!
	QPointF radiusP{radius, radius};
	radiusP = viewport->fromMetresToPixels(radiusP);
	radius = std::max(radiusP.x(), radiusP.y());
	setGeometry(graphicalEntity->getPosition(), radius);
}


