/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Effects/AntipsychosisEffect.hpp"

#include "Common/Enums.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Location.hpp"
#include "Graphics/Entities/GraphicalEntity.hpp"
#include "UserInterface/Viewport/Viewport.hpp"


AntipsychosisEffect::AntipsychosisEffect(const Viewport *viewport, const float radius)
		: CircleEffect{viewport, sf::Color{181, 20, 125, 90}, sf::Color{181, 20, 125, 35}}, radius{radius}
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

	QPointF radiusP{radius, radius};
	radiusP = viewport->fromMetresToPixels(radiusP);
	setGeometry(graphicalEntity->getPosition(), std::max(radiusP.x(), radiusP.y()));
}


