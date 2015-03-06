/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore/QHash>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <SFML/Graphics.hpp>

#include "DataManager/DataManager.hpp"
#include "Graphics/Entities/Animation.hpp"


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
	const Animation *getAnimation(const QString &name);
	const sf::Font *getFont(const QString &name);

private:
	const DataManager *dataManager;

	QHash<QString, QPair<sf::Texture *, int>> textures;
	QHash<QString, QPair<Animation *, int>> animations;
	QHash<QString, QPair<sf::Font *, int>> fonts;
};