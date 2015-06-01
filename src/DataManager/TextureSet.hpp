/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QHash>
#include <QPair>
#include <QString>

#include "DataManager/ImageMetaData.hpp"
#include "DataManager/Resource.hpp"
#include "DataManager/TextureData.hpp"


/**
 * @brief A set of textures indexed with ImageMetaData.
 */
class TextureSet {
public:
	typedef QList<QPair<ImageMetaData, Resource *>> Frames;
	TextureSet(const QList<QPair<QString, TextureData *>> &textures);

	/**
	 * @brief Returns images for all frames for every combination of State, Direction, Frame number etc available in
	 * the texture set.
	 */
	Frames getAllImages() const;

private:
	Frames images;
};
