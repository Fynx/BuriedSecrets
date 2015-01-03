/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Graphics.hpp"


Graphics::Graphics(const PhysicsEngine *physicsEngine, const DataManager* dataManager)
	: graphicsDataManager{dataManager}, widget{new GraphicsWidget}, graphicalEntityFactory{&graphicsDataManager}
	, physicsEngine{physicsEngine}, dataManager{dataManager}, camera{nullptr}, mapSprite{nullptr}
{
	canvas = widget;
}


Graphics::~Graphics()
{
	delete mapSprite;
	mapSprite = nullptr;
	delete camera;
}


GraphicsWidget * Graphics::getGraphicsWidget()
{
	return widget;
}


void Graphics::startRendering(const Viewport *viewport, int framesIntervalms)
{
	delete camera;
	camera = new Camera{physicsEngine, viewport};
	renderTimer.setInterval(framesIntervalms);
	connect(&renderTimer, SIGNAL(timeout()), this, SLOT(render()));
	renderTimer.start();
}


void Graphics::loadMap(const Map *map)
{
	this->map = map;
	mapSprite = new sf::Sprite{*(graphicsDataManager.getTexture(map->getMapInfo()->getName()))};
	mapSprite->setPosition(0, 0);
}


void Graphics::render()
{
	canvas->clear(sf::Color::Black);
	// Draw the map
	// FIXME TODO moving the map (view, etc)
	if (mapSprite != nullptr) {
		canvas->draw(*mapSprite);
	}

	// All the drawing logic for objects goes here.

	auto visibleObjects = camera->getVisibleObjects();
	auto visibleGraphicalEntities = getGraphicalEntitiesFor(visibleObjects);

	// TODO depth - probably need to sort visible objects by the layer on which they should be.

	for (auto& obj: visibleGraphicalEntities) {
		updateEntity(obj, 0);
		canvas->draw(*(obj->getDrawable()));
	}

	// This call has to be at the end to repaint the widget.
	widget->repaint();
}


QVector<GraphicalEntity *> Graphics::getGraphicalEntitiesFor(const QList<const Object *> &objects)
{
	QVector<GraphicalEntity *> res;
	for (const auto& obj: objects) {
		res.append(graphicalEntityFactory.get(obj));
	}
	return res;
}


void Graphics::updateEntity(GraphicalEntity *entity, const float deltaTime)
{
	entity->setDirection(static_cast<BS::Graphic::Direction>(
			camera->discretizeAngle(physicsEngine->getAngle(entity->getObject()))));
	entity->setPosition(camera->getPerspective()->getTranslatedPoint(
			physicsEngine->getPosition(entity->getObject())));
	entity->update(deltaTime);
}

