/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <SFML/Graphics.hpp>

#include "UserInterface/BoardWidget.hpp"


/**
 * @brief This class represents the widget on which the main game screen is drawn.
 *
 * This is the subclass of an actual UI widget which adds SFML-related functionality needed for drawing.
 */
class GraphicsWidget: public BoardWidget, public sf::RenderWindow {
Q_OBJECT;
public:
	GraphicsWidget();
	sf::RenderWindow *getCanvas();

protected:
	virtual QPaintEngine * paintEngine() const;
	virtual void showEvent(QShowEvent *);
	virtual void paintEvent(QPaintEvent *);

	bool initialized;
};
