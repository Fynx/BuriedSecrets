/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QList>
#include <QPair>
#include <QString>

#include "Common/Enums.hpp"
#include "DataManager/Resource.hpp"


class TextureData {
public:
	typedef QList<QPair<QPair<BS::Graphic::Direction, int>, Resource *>> TextureFrames;

	TextureData(const int rows, const int columns, const QByteArray &data);
	~TextureData();
	TextureFrames getFrames();

private:
	TextureFrames frames;
};