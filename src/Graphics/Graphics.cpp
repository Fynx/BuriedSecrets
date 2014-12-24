/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Graphics.hpp"


Graphics::Graphics(const PhysicsEngine *physicsEngine, const DataManager* dataManager)
	: graphicsDataManager{dataManager}, widget{}, graphicalEntityFactory{&graphicsDataManager}, physicsEngine{physicsEngine}
	, dataManager{dataManager}
{
	canvas = &widget;
}


GraphicsWidget *Graphics::getGraphicsWidget()
{
	return &widget;
}


void Graphics::startRendering(const Viewport *viewport, int framesIntervalms)
{
	// TODO
	// Move all rendering logic into a separate class (Renderer) and forward viewport there.
	renderTimer.setInterval(framesIntervalms);
	connect(&renderTimer, SIGNAL(timeout()), this, SLOT(render()));
	renderTimer.start();
}


void Graphics::render()
{
	canvas->clear(sf::Color::Black);
	// All the drawing logic for objects goes here.

	auto sceneRect = QRectF(0, 0, 200, 300);	// FIXME this is just temporary, it should be obtained from somewhere.
	auto visibleObjects = physicsEngine->getObjectsInRect(sceneRect);
	auto visibleGraphicalEntities = getGraphicalEntitiesFor(visibleObjects);

	// TODO depth - probably need to sort visible objects by the layer on which they should be.

	for (auto& obj: visibleGraphicalEntities) {
		// FIXME delta time temporary
		updateEntity(obj, 0);
		canvas->draw(*(obj->getDrawable()));
	}

	// This call has to be at the end to repaint the widget.
	widget.repaint();
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
	entity->setPosition(physicsEngine->getPosition(entity->getObject()));
	entity->update(deltaTime);
}

