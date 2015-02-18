/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QTimer>
#include <SFML/Graphics.hpp>

#include "UserInterface/BoardWidget.hpp"

class GraphicsWidget : public BoardWidget, public sf::RenderWindow {
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