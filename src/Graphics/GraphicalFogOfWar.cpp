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
	textureSize.setWidth(sizeP.x());
	textureSize.setHeight(sizeP.y());
	FOWTexture.create(textureSize.width(), textureSize.height());
	FOWTexture.clear(sf::Color::Black);
	// TODO zoom.
}


void GraphicalFogOfWar::update()
{
	circle.setRadius(rand() % 50);
	circle.setPosition(rand() % (int)textureSize.width(),
			   textureSize.height() - (rand() % (int)textureSize.height()));

	circle.setPointCount(20);
	circle.setFillColor(sf::Color::Transparent);
	FOWTexture.draw(circle, sf::RenderStates{sf::BlendMode::BlendMultiply});

	FOWSprite.setTexture(FOWTexture.getTexture());
	FOWSprite.setPosition(0, 0);
}


void GraphicalFogOfWar::draw()
{
	renderTarget->draw(FOWSprite);
}

