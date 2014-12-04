/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Graphics.hpp"


Graphics::Graphics(const Mind* mind, const DataManager* dataManager)
: graphicsDataManager{dataManager}, widget{}, graphicalEntityFactory{&graphicsDataManager}, mind{mind}, dataManager{dataManager}
{
	canvas = &widget;
}


GraphicsWidget *Graphics::getGraphicsWidget()
{
	return &widget;
}


void Graphics::startRendering(int framesIntervalms)
{
	renderTimer.setInterval(framesIntervalms);
	connect(&renderTimer, SIGNAL(timeout()), this, SLOT(render()));
	renderTimer.start();
}


void Graphics::render()
{
	canvas->clear(sf::Color::Black);
	// All the drawing logic for objects goes here.

	auto sceneRect = QRect();	// FIXME this is just temporary, it should be obtained from somewhere.
	auto visibleObjects = mind->getObjectsInRect(sceneRect);
	auto visibleGraphicalEntities = getGraphicalEntitiesFor(visibleObjects);

	// TODO depth - probably need to sort visible objects by the layer on which they should be.

	for (const auto& obj: visibleGraphicalEntities) {
		canvas->draw(*(obj->getDrawable()));
	}
	// This call has to be at the end to repaint the widget.
	widget.repaint();
}


QVector<GraphicalEntity *> Graphics::getGraphicalEntitiesFor(const QVector<Object *> &objects)
{
	QVector<GraphicalEntity *> res;
	for (const auto& obj: objects) {
		res.append(graphicalEntityFactory.get(obj));
	}
	return res;
}
