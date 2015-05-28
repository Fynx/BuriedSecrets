/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QVector>
#include <SFML/Graphics.hpp>

#include "Graphics/Entities/GraphicalEntity.hpp"
#include "Graphics/GraphicsDataManager.hpp"

class Camera;
class DecalManager;
class GraphicalEffectFactory;
class GraphicalEntityFactory;
class GraphicalFogOfWar;
class GraphicsWidget;
class MapManager;
class Mind;
class PhysicsEngine;
class Viewport;


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
	 */
	void loadMap();

	// Toggle display of FPS / FOW.
	void toggleShowFPS();
	void toggleFogOfWar();

private:
	QVector<GraphicalEntity *> getGraphicalEntitiesFor(const QList<const Object *> &objects);
	void updateEntity(GraphicalEntity *entity, const float deltaTime, const QPointF &position);
	/**
	 * @brief Returns the graphical position of the entity.
	 */
	QPointF getPosition(GraphicalEntity *entity) const;
	/**
	 * @brief Draws the rubber band selection (if needed).
	 */
	void drawRubberBand();
	/**
	 * @brief Draws the FPS counter.
	 */
	void drawFPS();
	/**
	 * @brief Gets effects from mind and updates the inside state of entities to use them.
	 */
	void updateEffects(QVector<GraphicalEntity *> &visibleEntities);
	/**
	 * @brief Draws the decal for a given effect.
	 *
	 * This method assumes nothing about the effect and draws it if it actually is a decal.
	 *
	 * @return True if the effect was a Decal.
	 */
	bool handleDecal(const Effect &effect);

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
	sf::RenderTexture mapRenderTexture;

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
	DecalManager *decalManager;

private slots:
	/**
	 * @brief Renders the current scene.
	 *
	 * NOT thread-safe.
	 */
	void render();
};
