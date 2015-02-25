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

	tempTexture.create(0, 0);

	circle.setPointCount(40);
	circle.setFillColor(sf::Color::Transparent);
	circle.setScale(scale.x(), scale.y());

	polygon.setFillColor(sf::Color::Black);
	// TODO zoom.
}


void GraphicalFogOfWar::update()
{
	auto *updateDiff = mapManager->getVisibilityUpdatesDiff();

	for (const auto& visUpdate: *updateDiff) {
		QPointF radiusP = {visUpdate.includeCircle.radius, visUpdate.includeCircle.radius};
		radiusP = viewport->fromMetresToPixels(radiusP);

		// Resize texture only when needed.
		if (tempTexture.getSize().x < radiusP.x() * 2 || tempTexture.getSize().y < radiusP.y() * 2) {
			tempTexture.create(radiusP.x() * 2.0f, radiusP.y() * 2.0f);
		}
		tempTexture.clear(sf::Color::Black);

		circle.setRadius(std::max(radiusP.x(), radiusP.y()));

		QPointF realPos = viewport->fromMetresToPixels(visUpdate.includeCircle.centre);
		circle.setPosition(0, tempTexture.getSize().y - 2.0f * radiusP.y());
		tempTexture.draw(circle, sf::RenderStates{sf::BlendMode::BlendMultiply});

		for (const BS::Geometry::Polygon &poly: visUpdate.ommitPolygons) {
			polygon.setPointCount(poly.length());

			for (int i = 0; i < poly.length(); ++i) {
				QPointF p = viewport->fromMetresToPixels(poly[i]);
				polygon.setPoint(i, sf::Vector2f{(float)(p.x() - realPos.x() + radiusP.x()),
						(float)(p.y() - realPos.y() + radiusP.y())});
			}

			tempTexture.draw(polygon);
		}

		tempSprite.setTexture(tempTexture.getTexture());
		// Y is flipped when drawing on RenderTexture.
		tempSprite.setPosition(realPos.x() - radiusP.x(), textureSize.height() - realPos.y() - radiusP.y());
		FOWTexture.draw(tempSprite, sf::RenderStates{sf::BlendMode::BlendMultiply});
	}

	FOWSprite.setTexture(FOWTexture.getTexture());
	delete updateDiff;
}


void GraphicalFogOfWar::draw()
{
	renderTarget->draw(FOWSprite);
}

