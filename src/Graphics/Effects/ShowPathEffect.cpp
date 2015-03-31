/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Effects/ShowPathEffect.hpp"

#include "Common/Enums.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Graphics/Entities/GraphicalEntity.hpp"


ShowPathEffect::ShowPathEffect(const Viewport *viewport): GraphicalEffect{viewport} {
	line.setColor(sf::Color::Red);
	line.setThickness(2.5f);
	pointShape.setSize(sf::Vector2f{1.5f, 1.5f});
	pointShape.setFillColor(sf::Color::Yellow);
}


void ShowPathEffect::draw(const GraphicalEntity *graphicalEntity, sf::RenderTarget *renderTarget)
{
	const Unit *unit = dynamic_cast<const Unit *>(graphicalEntity->getObject());
	if (unit == nullptr) {
		warn("Trying to show path for non-unit object: " + graphicalEntity->getObject()->getName());
	}
	QList<QPointF> path = unit->getCurrentPath();
	QPointF prev = graphicalEntity->getPosition();
	for (auto p: path) {
		p = viewport->fromMetresToPixels(p);
		line.setPoints(prev, p);
		renderTarget->draw(line);
		prev = p;
	}

	for (auto p: path) {
		p = viewport->fromMetresToPixels(p);
		pointShape.setPosition(p.x() - pointShape.getSize().x / 2.0f, p.y() - pointShape.getSize().y / 2.0f);
		renderTarget->draw(pointShape);
	}
}


int ShowPathEffect::getOrderId() const
{
	return BS::Graphic::EffectOrder::ShowPath;
}


