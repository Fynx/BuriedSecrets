/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicalFogOfWar.hpp"


GraphicalFogOfWar::GraphicalFogOfWar(sf::RenderTarget *renderTarget, MapManager *mapManager, const Viewport *viewport)
	: renderTarget{renderTarget}, mapManager{mapManager}, viewport{viewport}
{
	const QSizeF size = mapManager->getMap()->getSize();
	QPointF sizeP{size.width(), size.height()};
	sizeP = viewport->fromMetresToPixels(sizeP);
	QPointF scale = viewport->getWholeScale();
	float maxScale = std::max(scale.x(), scale.y());
	scale /= maxScale;

	textureSize.setWidth(sizeP.x());
	textureSize.setHeight(sizeP.y());

	FOWTexture.create(textureSize.width(), textureSize.height());
	FOWTexture.clear(sf::Color::Black);
	FOWSprite.setPosition(0, 0);

	circle.setPointCount(40);
	circle.setFillColor(sf::Color::Transparent);
	circle.setScale(scale.x(), scale.y());
	// TODO zoom.
}


void GraphicalFogOfWar::update()
{
	auto *updateDiff = mapManager->getVisibilityUpdatesDiff();

	for (const auto& visUpdate: *updateDiff) {
		QPointF radiusP = {visUpdate.includeCircle.radius, visUpdate.includeCircle.radius};
		radiusP = viewport->fromMetresToPixels(radiusP);
		circle.setRadius(std::max(radiusP.x(), radiusP.y()));

		QPointF pos = viewport->fromMetresToPixels(visUpdate.includeCircle.centre);
		// Y is flipped when drawing on RenderTexture.
		circle.setPosition(pos.x() - radiusP.x(), textureSize.height() - pos.y() - radiusP.y());

		FOWTexture.draw(circle, sf::RenderStates{sf::BlendMode::BlendMultiply});
	}

	FOWSprite.setTexture(FOWTexture.getTexture());
	delete updateDiff;
}


void GraphicalFogOfWar::draw()
{
	renderTarget->draw(FOWSprite);
}

