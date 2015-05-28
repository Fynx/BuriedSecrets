/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QtCore/QHash>
#include <QtCore/QPair>
#include <SFML/Graphics.hpp>

#include "Graphics/GraphicalTextureSet.hpp"

class DataManager;
class QString;


/**
 * @brief Data manager for graphical resources - textures, fonts etc.
 *
 * NOTE this class should be deleted AFTER deleting anything that uses the resources kept here.
 */
class GraphicsDataManager {
public:
	GraphicsDataManager(const DataManager *dataManager);
	~GraphicsDataManager();

	const GraphicalTextureSet *getTextureSet(const QString &name);
	const sf::Font *getFont(const QString &name);

private:
	const DataManager *dataManager;

	QHash<QString, QPair<GraphicalTextureSet *, int>> textureSets;
	QHash<QString, QPair<sf::Font *, int>> fonts;
};
