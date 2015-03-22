/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "DataManager/TextureSet.hpp"

#include <cassert>

#include <QRegExp>

#include "DebugManager/DebugManager.hpp"


TextureSet::TextureSet(const QList<QPair<QString, TextureData *>> &textures)
{
	// Parse the strings and create the list of images.
	QRegExp re("([A-Z][a-z]+)([A-Za-z ]*)");

	for (const auto &entry : textures) {
		ImageMetaData metaData;
		// Make sure that string parses.
		if (re.indexIn(entry.first) == -1) {
			err("Couldn't parse TextureSet, badly formatted texture label: '" + entry.first + "'");
			assert(false);
			return;
		}

		// Extract state and weapon from the string.
		metaData.state = BS::changeStringToState(re.cap(1));
		metaData.weapon = (re.captureCount() > 2) ?
				BS::changeStringToItemType(re.cap(2)) : BS::ItemType::Invalid;

		const auto &frames = entry.second->getFrames();
		for (const auto &frame : frames) {
			metaData.direction = frame.first.first;
			metaData.frame = frame.first.second;
			images.append({metaData, frame.second});
		}
	}
}


QList<QPair<ImageMetaData, Resource *>> TextureSet::getAllImages() const
{
	return images;
}

