/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include <cassert>

#include "Graphics/GraphicsDataManager.hpp"


using namespace sf;


GraphicsDataManager::GraphicsDataManager(const DataManager* dataManager)
: dataManager{dataManager}
{
}


GraphicsDataManager::~GraphicsDataManager()
{
	for (auto& elem: textures) {
		delete elem.first;
	}
	// The rest is going to clean itself.
}


const sf::Texture* GraphicsDataManager::getTexture(const QString& name)
{
	Texture *result;

	auto it = textures.find(name);
	if (it == textures.end()) {
		const Resource *image = dataManager->getResource(name);
		result = new Texture();
		result->setSmooth(true);
		if (!result->loadFromMemory(image->getData(), image->getDataLength())) {
			qDebug() << "Failed to load the texture: " << name;
			qDebug() << image->getData();
			// TODO should we die miserably here?
		}
		textures[name] = QPair<Texture *, int>(result, 1);
	} else {
		it->second++;
		result = it->first;
	}

	return result;
}

