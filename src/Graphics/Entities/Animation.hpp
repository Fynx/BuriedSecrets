/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtCore/QHash>
#include <QtCore/QVector>
#include <SFML/Graphics.hpp>


#include "GameObjects/Object.hpp"


class Animation {
public:
	typedef QVector<QVector<const sf::Texture *>> FramesList;
	Animation(const Animation::FramesList &frames);
	Animation(Animation::FramesList &&frames);

	/**
	 * @brief Returns the frame for a given direction the object is facing and the frame id.
	 */
	const sf::Texture *getFrame(const int direction, const int id) const;
private:
	FramesList frames;
};