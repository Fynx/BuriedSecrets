/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/GraphicalFogOfWar.hpp"

#include "Mind/MapManager/MapManager.hpp"
#include "UserInterface/Viewport/Viewport.hpp"


// Potential TODO/FIXME: This class may benefit from the use of shaders to speed things up.


GraphicalFogOfWar::GraphicalFogOfWar(sf::RenderTarget *renderTarget, MapManager *mapManager, const Viewport *viewport)
	: renderTarget{renderTarget}, mapManager{mapManager}, viewport{viewport}
{
	const QSizeF size = mapManager->getMap()->getSize();
	QPointF sizeP{size.width(), size.height()};
	sizeP = viewport->fromMetresToPixels(sizeP);

	QPointF scale = viewport->getWholeScale();
	float maxScale = std::max(scale.x(), scale.y());
	scale /= maxScale;

	FOWTexture.create(sizeP.x(), sizeP.y());
	FOWTexture.clear(sf::Color::Black);
	FOWSprite.setPosition(0, 0);

	FOVTexture.create(sizeP.x(), sizeP.y());
	FOVSprite.setPosition(0, 0);

	tempTexture.create(0, 0);

	circle.setPointCount(40);
	circle.setFillColor(sf::Color::Transparent);
	circle.setScale(scale.x(), scale.y());

	polygon.setFillColor(sf::Color::Black);
	// TODO zoom.
}


void GraphicalFogOfWar::update()
{
	// FOW
	auto *updateDiff = mapManager->getVisibilityUpdatesDiff();
	if (updateDiff->length() > 0) {
		drawFOVs(FOWTexture, *updateDiff);
		FOWSprite.setTexture(FOWTexture.getTexture());

		// FOV
		// Clear previous visible region.
		FOVTexture.clear(sf::Color::Black);

		// Get and draw the current visible region.
		auto visibleRegion = mapManager->getVisibleRegion();
		drawFOVs(FOVTexture, visibleRegion);
		FOVSprite.setTexture(FOVTexture.getTexture());
		FOVSprite.setColor(sf::Color{255, 255, 255, 100});
	}
	delete updateDiff;
}


void GraphicalFogOfWar::draw()
{
	renderTarget->draw(FOVSprite);
	renderTarget->draw(FOWSprite);
}


void GraphicalFogOfWar::drawFOVs(sf::RenderTexture& canvas, const VisibilityUpdateDiff& updateDiff)
{
	for (const auto &visUpdate: updateDiff) {
		QPointF radiusP = {visUpdate.includeCircle.radius, visUpdate.includeCircle.radius};
		radiusP = viewport->fromMetresToPixels(radiusP);

		// Resize texture only when needed.
		if ((tempTexture.getSize().x < radiusP.x() * 2) || (tempTexture.getSize().y < radiusP.y() * 2)) {
			tempTexture.create(radiusP.x() * 4.0f, radiusP.y() * 4.0f);
		}
		tempTexture.clear(sf::Color::Black);

		circle.setRadius(std::max(radiusP.x(), radiusP.y()));

		QPointF realPos = viewport->fromMetresToPixels(visUpdate.includeCircle.centre);
		circle.setPosition(0, 0);
		tempTexture.draw(circle, sf::RenderStates{sf::BlendMode::BlendMultiply});

		for (const BS::Geometry::Polygon &poly: visUpdate.ommitPolygons) {
			polygon.setPointCount(poly.length());

			for (int i = 0; i < poly.length(); ++i) {
				QPointF p = viewport->fromMetresToPixels(poly[i]);
				polygon.setPoint(i, sf::Vector2f{
						(float)(p.x() - realPos.x() + radiusP.x()),
						(float)(p.y() - realPos.y() + radiusP.y())
				});
			}

			tempTexture.draw(polygon);
		}

		tempTexture.display();
		tempSprite.setTexture(tempTexture.getTexture());
		tempSprite.setPosition(realPos.x() - radiusP.x(), realPos.y() - radiusP.y());
		canvas.draw(tempSprite, sf::RenderStates{sf::BlendMode::BlendMultiply});
	}

	canvas.display();
}


