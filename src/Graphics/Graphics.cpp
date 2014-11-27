#include "Graphics/Graphics.hpp"


Graphics::Graphics(Mind* mind)
	: widget{}, mind{mind}
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
	auto visibleGraphicalObjects = getGraphicalObjectsFor(visibleObjects);

	// TODO depth - probably need to sort visible objects by the layer on which they should be.

	for (const auto& obj: visibleGraphicalObjects) {
		canvas->draw(*(obj->getDrawable()));
	}
	// This call has to be at the end to repaint the widget.
	widget.repaint();
}

QVector<GraphicalObject *> Graphics::getGraphicalObjectsFor(const QVector<Object *>& objects)
{
	QVector<GraphicalObject *> res;
	for (const auto& obj: objects) {
		res.append(graphicalObjectFactory.get(obj));
	}
	return res;
}
