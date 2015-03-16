/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "DataManager/TextureData.hpp"

#include <cassert>

#include <QBuffer>
#include <QImage>


TextureData::TextureData(const int rows, const int columns, const QString &data)
{
	// Extract frames and save them to resources.
	assert(rows == 1 || rows == 8);	// Other sizes not supported for now.

	QImage texture;
	texture.loadFromData((const uchar *)data.data(), data.length());

	QRect rect(0, 0, texture.width() / columns, texture.height() / rows);
	size_t offset = rect.x() * texture.depth() / 8 + rect.y() * texture.bytesPerLine();

	for (int dir = 0; dir < rows; ++dir) {
		for (int frame = 0; frame < columns; ++frame) {
			QBuffer imageData;
			QImage frameImage(texture.bits() + offset, rect.width(), rect.height(), texture.bytesPerLine(),
					texture.format());
			frameImage.save(&imageData);

			frames.append({{static_cast<BS::Graphic::Direction>(dir), frame},
				       new Resource(imageData.data().data(), imageData.data().length())});
		}
	}
}


TextureData::~TextureData()
{
	for (const auto &p : frames) {
		delete p.second;
	}
}


TextureData::TextureFrames TextureData::getFrames()
{
	return frames;
}


