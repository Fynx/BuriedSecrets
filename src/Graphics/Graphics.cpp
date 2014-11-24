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

	// FIXME This is just an example, to be removed.
	static sf::CircleShape circle(5);
	circle.setPosition(10, 10);
	circle.setFillColor(sf::Color::Green);
	canvas->draw(circle);

	// This call has to be at the end to repaint the widget.
	widget.repaint();
}
