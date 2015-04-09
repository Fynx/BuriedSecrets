/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QSizeF>
#include <SFML/Graphics.hpp>

class MapManager;
class Viewport;


/**
 * @brief This class manages the graphical representation of FogOfWar and can draw it.
 */
class GraphicalFogOfWar {
public:
	GraphicalFogOfWar(sf::RenderTarget *renderTarget, MapManager *mapManager, const Viewport *viewport);

	/**
	 * @brief Fetches the new data from map manager and updates the internal FOW representation.
	 */
	void update();
	/**
	 * @brief Draws FOW on the renderTarget.
	 */
	void draw();

private:
	sf::Sprite FOWSprite;
	sf::Sprite tempSprite;
	sf::RenderTexture FOWTexture;
	sf::RenderTexture tempTexture;
	sf::CircleShape circle;
	sf::ConvexShape polygon;
	QSizeF textureSize;

	sf::RenderTarget *renderTarget;
	MapManager *mapManager;
	const Viewport *viewport;
};