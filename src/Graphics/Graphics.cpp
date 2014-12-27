/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Graphics.hpp"


Graphics::Graphics(const PhysicsEngine *physicsEngine, const DataManager* dataManager)
	: graphicsDataManager{dataManager}, widget{new GraphicsWidget}, graphicalEntityFactory{&graphicsDataManager}, physicsEngine{physicsEngine}
	, dataManager{dataManager}, camera{nullptr}
{
	canvas = widget;
}


Graphics::~Graphics()
{
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


void Graphics::render()
{
	canvas->clear(sf::Color::Black);
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
	entity->setPosition(physicsEngine->getPosition(entity->getObject()));
	entity->update(deltaTime);
}

