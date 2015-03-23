/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "DataManager/TextureData.hpp"

#include <cassert>

#include <QBuffer>
#include <QDebug>
#include <QImage>


TextureData::TextureData(const int rows, const int columns, const QByteArray &data)
{
	// Extract frames and save them to resources.
	assert(rows == 1 || rows == 8);	// Other sizes not supported for now.

	QImage texture;
	if (!texture.loadFromData((const uchar *)data.data(), data.length())) {
		qDebug() << "Couldn't read the image from the data!";
		assert(false);
	}

	int frameWidth = texture.width() / columns;
	int frameHeight = texture.height() / rows;

	for (int dir = 0; dir < rows; ++dir) {
		for (int frame = 0; frame < columns; ++frame) {
			QBuffer imageData;
			QImage frameImage = texture.copy(frame * frameWidth, dir * frameHeight,
							 frameWidth, frameHeight);
			frameImage.save(&imageData, "PNG");

			frames.append({
					{rows > 1 ? static_cast<BS::Graphic::Direction>(dir) :
							BS::Graphic::Direction::Invalid, frame},
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


