/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Entities/ShotEffectGraphicalEntity.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/PointToPointEffectData.hpp"
#include "UserInterface/Viewport/Viewport.hpp"


ShotEffectGraphicalEntity::ShotEffectGraphicalEntity(const Viewport *viewport)
	: EffectGraphicalEntity{viewport}
{
	line.setColor(sf::Color{131, 143, 145});
	line.setThickness(2.0f);
}


void ShotEffectGraphicalEntity::draw(sf::RenderTarget *renderTarget)
{
	renderTarget->draw(line);
}


void ShotEffectGraphicalEntity::update(const float timeDelta)
{}


void ShotEffectGraphicalEntity::updateData(const EffectData *effectData)
{
	const PointToPointEffectData *ptpData = dynamic_cast<const PointToPointEffectData *>(effectData);
	if (ptpData == nullptr) {
		err("Cannot update data for Shot Effect Entity!");
		// FIXME: Removed the assertion because this should not cause many problems, but this sometimes pops up.
// 		Q_ASSERT(false);
		return;
	}

	QPointF source = viewport->fromMetresToPixels(ptpData->getSource());
	QPointF destination = viewport->fromMetresToPixels(ptpData->getDestination());
	GraphicalEntity::setPosition((source + destination) / 2.0f);
	line.setPoints(source, destination);
}



