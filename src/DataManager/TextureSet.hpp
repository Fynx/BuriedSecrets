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


class TextureSet {
public:
	TextureSet(const QList<QPair<QString, TextureData *>> &textures);

	/**
	 * @brief Returns images for all frames for every combination of State, Direction, Frame number etc available in
	 * the texture set.
	 */
	QList<QPair<ImageMetaData, Resource *>> getAllImages();

private:
	QList<QPair<ImageMetaData, Resource *>> images;
};