/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Graphics.hpp"


Graphics::Graphics(const PhysicsEngine *physicsEngine, const DataManager* dataManager)
	: graphicsDataManager{dataManager}, showBasePolygons{false}, widget{new GraphicsWidget}
	, graphicalEntityFactory{nullptr}, physicsEngine{physicsEngine}, dataManager{dataManager}, camera{nullptr}
	, mapSprite{nullptr}
{
	canvas = widget;
}


Graphics::~Graphics()
{
	delete mapSprite;
	mapSprite = nullptr;
	delete camera;
}


GraphicsWidget * Graphics::getGraphicsWidget()
{
	return widget;
}


void Graphics::startRendering(const Viewport *viewport, int framesIntervalms)
{
	delete camera;
	camera = new Camera{physicsEngine, viewport};

	delete graphicalEntityFactory;
	graphicalEntityFactory = new GraphicalEntityFactory{&graphicsDataManager, viewport->getPerspective()};

	renderTimer.setInterval(framesIntervalms);
	connect(&renderTimer, SIGNAL(timeout()), this, SLOT(render()));
	renderTimer.start();
}


void Graphics::loadMap(const Map *map)
{
	this->map = map;
	mapSprite = new sf::Sprite{*(graphicsDataManager.getTexture(map->getMapInfo()->getName()))};
	mapSprite->setPosition(0, 0);
}


void Graphics::toggleShowBasePolygons()
{
	showBasePolygons = !showBasePolygons;
}


void Graphics::render()
{
	canvas->clear(sf::Color::Black);
	// Draw the map
	// FIXME TODO moving the map (view, etc)
	if (mapSprite != nullptr) {
		canvas->draw(*mapSprite);
	}

	// All the drawing logic for objects goes here.

	auto visibleObjects = camera->getVisibleObjects();
	auto visibleGraphicalEntities = getGraphicalEntitiesFor(visibleObjects);

	// TODO depth - probably need to sort visible objects by the layer on which they should be.

	for (auto& obj: visibleGraphicalEntities) {
		updateEntity(obj, 0);
		canvas->draw(*(obj->getDrawable()));

		if (showBasePolygons) {
			// FIXME this can not work for non-convex
			const auto points = obj->getBasePolygon();
			QPointF centre = obj->getBaseCentre();
			QPointF pos = getPosition(obj);
			sf::ConvexShape polygon;
			polygon.setPointCount(points.size());
			for (int i = 0; i < points.size(); ++i) {
				polygon.setPoint(i, sf::Vector2f(pos.x() - centre.x() + points[i].x(),
								 pos.y() - centre.y() + points[i].y()));
			}
			polygon.setFillColor(sf::Color::Transparent);
			polygon.setOutlineThickness(2);
			polygon.setOutlineColor(sf::Color::Red);
			canvas->draw(polygon);
		}
	}

	// This call has to be at the end to repaint the widget.
	widget->repaint();
}


QVector<GraphicalEntity *> Graphics::getGraphicalEntitiesFor(const QList<const Object *> &objects)
{
	QVector<GraphicalEntity *> res;
	for (const auto& obj: objects) {
		res.append(graphicalEntityFactory->get(obj));
	}
	return res;
}


void Graphics::updateEntity(GraphicalEntity *entity, const float deltaTime)
{
	entity->setDirection(static_cast<BS::Graphic::Direction>(
			camera->discretizeAngle(physicsEngine->getAngle(entity->getObject()))));
	entity->setPosition(getPosition(entity));
	entity->update(deltaTime);
}

QPointF Graphics::getPosition(GraphicalEntity *entity) const
{
	return camera->getPerspective()->getTranslatedPoint(physicsEngine->getPosition(entity->getObject()));
}


