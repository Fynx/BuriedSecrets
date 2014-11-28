/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <QtCore/QVector>

#include "Graphics/GraphicsWidget.hpp"
#include "Graphics/GraphicalObject.hpp"
#include "Graphics/GraphicalObjectFactory.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/UserInterface.hpp"


/**
 * This class is responsible for drawing the world as visible to the player.
 */
class Graphics: public QObject {
Q_OBJECT;
public:
	Graphics(const Mind *mind, const DataManager *dataManager);
	GraphicsWidget *getGraphicsWidget();
	/**
	 * @brief Starts periodical rendering.
	 *
	 * @param framesIntervalms Minimal interval between two consecutive frames in ms. Defaults to 0, which means
	 * 'as fast as possible'.
	 */
	void startRendering(int framesIntervalms = 0);
	/**
	 * @brief Loads the graphical representation of the level.
	 *
	 * @return void
	 */
	void loadLevel();

private:
	QVector<GraphicalObject *> getGraphicalObjectsFor(const QVector< Object* >& objects);

	GraphicsWidget widget;
	GraphicalObjectFactory graphicalObjectFactory;
	QTimer renderTimer;

	// This pointer is just for convenience as it points to the widget.
	sf::RenderWindow *canvas;
	const Mind *mind;
	const DataManager *dataManager;

private slots:
	/**
	 * @brief Renders the current scene.
	 */
	void render();
};