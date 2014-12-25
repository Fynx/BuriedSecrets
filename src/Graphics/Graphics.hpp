/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <QtCore/QVector>

#include "Graphics/Camera.hpp"
#include "Graphics/GraphicsWidget.hpp"
#include "Graphics/GraphicalEntity.hpp"
#include "Graphics/GraphicalEntityFactory.hpp"
#include "Graphics/GraphicsDataManager.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "UserInterface/Viewport.hpp"


/**
 * This class is responsible for drawing the world as visible to the player.
 */
class Graphics: public QObject {
Q_OBJECT;
public:
	Graphics(const PhysicsEngine *physicsEngine, const DataManager *dataManager);
	~Graphics();

	Graphics(const Graphics &other) = delete;
	Graphics &operator=(const Graphics &other) = delete;

	GraphicsWidget *getGraphicsWidget();
	/**
	 * @brief Starts periodical rendering.
	 *
	 * @param framesIntervalms Minimal interval between two consecutive frames in ms. Defaults to 0, which means
	 * 'as fast as possible'.
	 */
	void startRendering(const Viewport *viewport, int framesIntervalms = 0);
	/**
	 * @brief Loads the graphical representation of the level.
	 *
	 * @return void
	 */
	void loadLevel();

private:
	QVector<GraphicalEntity *> getGraphicalEntitiesFor(const QList< const Object * > &objects);
	void updateEntity(GraphicalEntity *entity, const float deltaTime);

	GraphicsDataManager graphicsDataManager;
	GraphicsWidget widget;
	GraphicalEntityFactory graphicalEntityFactory;
	QTimer renderTimer;

	// This pointer is just for convenience as it points to the widget.
	sf::RenderWindow *canvas;
	const PhysicsEngine *physicsEngine;
	const DataManager *dataManager;
	Camera *camera;

private slots:
	/**
	 * @brief Renders the current scene.
	 */
	void render();
};