/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include <QHash>
#include <SFML/Graphics.hpp>

class Decal;
class Effect;
class MapManager;
class GraphicsDataManager;
class QString;
class Viewport;


/**
 * @brief This class manages decals, can draw them etc.
 *
 * Right now, it only supports drawing on the map.
 */
class DecalManager {
public:
	DecalManager(const MapManager *mapManager, sf::RenderTexture *mapTexture,
		     GraphicsDataManager *graphicsDataManager, const Viewport *viewport);
	/**
	 * @brief Draws the decal for the effect.
	 */
	void drawDecal(const Effect &effect);
	bool isDecal(const Effect &effect) const;

private:
	Decal *getDecal(const QString &decalName);

	QHash<QString, Decal *> decals;
	const MapManager *mapManager;
	sf::RenderTexture *mapTexture;
	GraphicsDataManager *graphicsDataManager;
	const Viewport *viewport;
};
