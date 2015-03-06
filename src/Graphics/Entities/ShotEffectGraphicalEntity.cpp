/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Entities/ShotEffectGraphicalEntity.hpp"

#include "DebugManager/DebugManager.hpp"


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
	if (!ptpData) {
		err("Cannot update data for Shot Effect Entity!");
		Q_ASSERT(false);
	}

	QPointF source = viewport->fromMetresToPixels(ptpData->getSource());
	QPointF destination = viewport->fromMetresToPixels(ptpData->getDestination());
	GraphicalEntity::setPosition((source + destination) / 2.0f);
	line.setPoints(source, destination);
}



