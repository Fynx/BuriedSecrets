/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QtCore/QHash>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <SFML/Graphics.hpp>

// #include "DataManager/DataManager.hpp"
#include "Graphics/Entities/Animation.hpp"
#include "Graphics/GraphicalTextureSet.hpp"


class DataManager;

/**
 * @brief Data manager for graphical resources - textures, fonts etc.
 *
 * Not, this class has to be deleted AFTER deleting anything that uses the resources kept here.
 */
class GraphicsDataManager {
public:
	GraphicsDataManager(const DataManager *dataManager);
	~GraphicsDataManager();

	/**
	 * @brief Returns a shared pointer to the texture (living in the graphics card memory).
	 *
	 * TODO At some point there might be a need to add some mechanism for removing the unneeded data.
	 *
	 * @param name The identifier of the resource.
	 */
	const sf::Texture *getTexture(const QString &name);
	// TODO remove this after migrating to new textures.
	const Animation *getAnimation(const QString &name);
	const GraphicalTextureSet *getTextureSet(const QString &name);
	const sf::Font *getFont(const QString &name);

private:
	const DataManager *dataManager;

	QHash<QString, QPair<sf::Texture *, int>> textures;
	QHash<QString, QPair<Animation *, int>> animations;
	QHash<QString, QPair<GraphicalTextureSet *, int>> textureSets;
	QHash<QString, QPair<sf::Font *, int>> fonts;
};