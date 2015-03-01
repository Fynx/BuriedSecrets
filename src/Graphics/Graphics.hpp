/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <QtCore/QVector>

#include "Graphics/Camera.hpp"
#include "Graphics/GraphicsWidget.hpp"
#include "Graphics/GraphicalEffectFactory.hpp"
#include "Graphics/GraphicalEntity.hpp"
#include "Graphics/GraphicalEntityFactory.hpp"
#include "Graphics/GraphicalFogOfWar.hpp"
#include "Graphics/GraphicsDataManager.hpp"
#include "Mind/MapManager/Map.hpp"
#include "Mind/Mind.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "UserInterface/Viewport.hpp"


/**
 * This class is responsible for drawing the world as visible to the player.
 */
class Graphics: public QObject {
Q_OBJECT;
public:
	Graphics(const PhysicsEngine *physicsEngine, const DataManager *dataManager, Mind *mind);
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
	void pauseRendering();
	void resumeRendering();
	/**
	 * @brief Loads the graphical representation of the map.
	 *
	 * @return void
	 */
	void loadMap();
	void toggleShowFPS();
	void toggleFogOfWar();

private:
	QVector<GraphicalEntity *> getGraphicalEntitiesFor(const QList< const Object * > &objects);
	void updateEntity(GraphicalEntity *entity, const float deltaTime, const QPointF &position);
	/**
	 * @brief Returns the graphical position of the entity.
	 */
	QPointF getPosition(GraphicalEntity *entity) const;
	/**
	 * @brief Draws the rubber band selection (if needed).
	 */
	void drawRubberBand();
	void drawFPS();
	/**
	 * @brief Updates and draws Fog of War if enabled.
	 */
	void drawFOW();
	/**
	 * @brief Gets effects from mind and updates the inside state of entities to use them.
	 */
	void updateEffects(QVector<GraphicalEntity *> &visibleEntities);

	GraphicsDataManager graphicsDataManager;
	QTimer renderTimer;
	bool showFPS;
	bool showFOW;
	sf::Text fpsText;
	float timeElapsed;
	sf::Clock clock;
	int frames;
	sf::RectangleShape rubberBand;
	QSet<GraphicalEntity *> wasReset;	// A helper set for updating effects.

	// This pointer is just for convenience as it points to the widget.
	sf::RenderWindow *canvas;
	GraphicsWidget *widget;
	GraphicalEntityFactory *graphicalEntityFactory;
	const PhysicsEngine *physicsEngine;
	const DataManager *dataManager;
	Mind *mind;
	MapManager *mapManager;
	Camera *camera;
	sf::Sprite *mapSprite;
	int *drawOrder;
	GraphicalFogOfWar *FOW;

private slots:
	/**
	 * @brief Renders the current scene.
	 *
	 * NOT thread-safe.
	 */
	void render();
};
