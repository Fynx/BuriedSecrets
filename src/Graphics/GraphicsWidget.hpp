/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QTimer>
#include <SFML/Graphics.hpp>


class GraphicsWidget : public QWidget, public sf::RenderWindow {
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