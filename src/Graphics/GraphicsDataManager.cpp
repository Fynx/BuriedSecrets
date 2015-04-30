/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/GraphicsDataManager.hpp"

#include <cassert>

#include "DataManager/DataManager.hpp"


using namespace sf;


GraphicsDataManager::GraphicsDataManager(const DataManager* dataManager)
	: dataManager{dataManager}
{}


GraphicsDataManager::~GraphicsDataManager()
{
	for (auto &elem: fonts) {
		delete elem.first;
	}
	for (auto &elem: textureSets) {
		delete elem.first;
	}
	// The rest is going to clean itself.
}


const GraphicalTextureSet *GraphicsDataManager::getTextureSet(const QString &name)
{
	GraphicalTextureSet *result = nullptr;

	auto it = textureSets.find(name);
	if (it == textureSets.end()) {
		const TextureSet *textureSet = dataManager->getTextureSet(name);
		const auto &frames = textureSet->getAllImages();
		GraphicalTextureSet::FrameSet frameSet;

		for (const auto &frameDesc : frames) {
			Texture *texture = new sf::Texture{};
			texture->setSmooth(true);
			if (!texture->loadFromMemory(frameDesc.second->getData(), frameDesc.second->getDataLength())) {
				qDebug() << "Failed to load the texture: " << name;
				// TODO should we die miserably here?
			}
			frameSet.insert(frameDesc.first, texture);
		}

		result = new GraphicalTextureSet{frameSet};
		textureSets[name] = QPair<GraphicalTextureSet*, int>{result, 1};
	} else {
		it->second++;
		result = it->first;
	}

	if (result == nullptr) {
		err("No texture for: " + name);
	}
	return result;
}


const Font *GraphicsDataManager::getFont(const QString &name)
{
	Font *result;

	auto it = fonts.find(name);
	if (it == fonts.end()) {
		const Resource *res = dataManager->getResource(name);

		result = new Font();
		if (!result->loadFromMemory(res->getData(), res->getDataLength())) {
			qDebug() << "Failed to load the font: " << name;
		}

		fonts[name] = QPair<Font *, int>{result, 1};
	} else {
		it->second++;
		result = it->first;
	}

	return result;
}
