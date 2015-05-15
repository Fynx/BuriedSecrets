/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QSizeF>
#include <SFML/Graphics.hpp>

#include "Mind/MapManager/VisibilityUpdate.hpp"

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
	 * @brief Draws the FOW.
	 */
	void draw();

private:
	/**
	 * @brief Draws updates to the visibility to a FOV on canvas.
	 */
	void drawUpdates(sf::RenderTexture& canvas, const VisibilityUpdateDiff& updateDiff, const QRectF &view,
			 const float scale);
	void enlargeAndBlur(const sf::Texture &texture, sf::RenderTexture &target, const QPointF &topLeft,
			    const QPointF &bottomRight, const float scale, const sf::Shader &shader);

	float FOWSizeScale;
	float FOVSizeScale;
	QPoint previousTopLeft;
	QPoint previousBottomRight;
	int previousVisibleRegionSize;

	sf::Sprite FOVSprite;
	sf::Sprite FOWSprite;

	sf::Shader blurHShader;
	sf::Shader blurVShader;

	sf::RenderTexture FOVTexture;
	sf::RenderTexture FOVOneShaderTexture;
	sf::RenderTexture FOVScreenTexture;
	sf::RenderTexture FOWTexture;
	sf::RenderTexture FOWScreenTexture;
	sf::RenderTexture tempTexture;

	sf::CircleShape circle;
	sf::ConvexShape polygon;

	sf::RenderTarget *renderTarget;
	MapManager *mapManager;
	const Viewport *viewport;
};
