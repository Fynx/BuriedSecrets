/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Graphics.hpp"

#include "Graphics/BasePolygonEffect.hpp"
#include "Graphics/SelectionEffect.hpp"


Graphics::Graphics(const PhysicsEngine *physicsEngine, const DataManager* dataManager)
	: graphicsDataManager{dataManager}, showFPS{true}, timeElapsed{0.0f}, frames{0}
	, widget{new GraphicsWidget}, graphicalEntityFactory{nullptr}, physicsEngine{physicsEngine}
	, dataManager{dataManager}, camera{nullptr}, mapSprite{nullptr}, drawOrder{new int[10000]}
	, positions{new QPointF[10000]}
{
	canvas = widget;
	fpsText.setFont(*graphicsDataManager.getFont("HEMIHEAD"));
	fpsText.setColor(sf::Color::Red);
	rubberBand.setFillColor(sf::Color{40, 200, 200, 127});
	rubberBand.setOutlineColor(sf::Color{50, 210, 210, 200});
	rubberBand.setOutlineThickness(1);
	widget->setVerticalSyncEnabled(true);

	addEffect("Selection", new SelectionEffect{}, preEffects);
}


Graphics::~Graphics()
{
	delete mapSprite;
	mapSprite = nullptr;
	delete camera;
	delete drawOrder;
}


GraphicsWidget *Graphics::getGraphicsWidget()
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


void Graphics::pauseRendering()
{
	renderTimer.stop();
}


void Graphics::resumeRendering()
{
	Q_ASSERT(camera);
	Q_ASSERT(graphicalEntityFactory);
	renderTimer.start();
}


void Graphics::loadMap(const Map *map)
{
	this->map = map;
	mapSprite = new sf::Sprite{*(graphicsDataManager.getTexture(map->getName()))};
	mapSprite->setPosition(0, 0);
}

void Graphics::toggleShowBasePolygons()
{
	if (!removeEffect("BasePolygons", postEffects)) {
		addEffect("BasePolygons", new BasePolygonEffect{}, postEffects);
	}
}

void Graphics::toggleShowFPS()
{
	showFPS = !showFPS;
	clock.restart();
	timeElapsed = 0.0f;
	frames = 0;
}

void Graphics::render()
{
	canvas->clear(sf::Color::Black);
	canvas->setView(camera->getCurrentView());

	// Draw the map
	if (mapSprite != nullptr) {
		canvas->draw(*mapSprite);
	}

	// All the drawing logic for objects goes here.
	auto visibleObjects = camera->getVisibleObjects();
	auto visibleGraphicalEntities = getGraphicalEntitiesFor(visibleObjects);

	for (int i = 0; i < visibleGraphicalEntities.size(); ++i) {
		drawOrder[i] = i;
		positions[i] = getPosition(visibleGraphicalEntities[i]);
	}

	qSort(drawOrder, drawOrder + visibleGraphicalEntities.size(),
	      [&](const int &a, const int &b) -> bool {
		QPointF aP = positions[a] + visibleGraphicalEntities[a]->getBaseCentre();
		QPointF bP = positions[b] + visibleGraphicalEntities[b]->getBaseCentre();

		if (aP.y() != bP.y()) {
			return aP.y() < bP.y();
		}

		return aP.x() < bP.x();
	      });


	GraphicalEntity *obj;

	// Draw pre effects (update entities as well).
	for (int i = 0, idx = drawOrder[0]; i < visibleGraphicalEntities.size(); idx = drawOrder[++i]) {
		obj = visibleGraphicalEntities[idx];
		updateEntity(obj, 0, positions[idx]);

		// TODO FIXME When refactoring graphics, one might want to bind viewport and canvas to the effect
		// (pass it in constructor or sth like that).
		for (const auto &effect: preEffects) {
			effect.second->draw(obj, positions[idx], camera->getViewport(), canvas);
		}
	}

	// Draw entities.
	for (int i = 0, idx = drawOrder[0]; i < visibleGraphicalEntities.size(); idx = drawOrder[++i]) {
		obj = visibleGraphicalEntities[idx];
		obj->draw(canvas);

		for (const auto &effect: postEffects) {
			effect.second->draw(obj, positions[idx], camera->getViewport(), canvas);
		}
	}

	// Draw post effects.
	for (int i = 0, idx = drawOrder[0]; i < visibleGraphicalEntities.size(); idx = drawOrder[++i]) {
		obj = visibleGraphicalEntities[idx];

		for (const auto &effect: postEffects) {
			effect.second->draw(obj, positions[idx], camera->getViewport(), canvas);
		}
	}

	drawRubberBand();

	if (showFPS) {
		++frames;
		float deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		timeElapsed += deltaTime;
		if (timeElapsed >= 1.0f) {
			timeElapsed -= 1.0f;
			fpsText.setString(std::to_string(frames));
			frames = 0;
		}

		sf::View view = canvas->getView();
		sf::Vector2f center = view.getCenter();
		fpsText.setPosition(center.x + view.getSize().x / 2 - 45, center.y - view.getSize().y / 2 + 20);
		canvas->draw(fpsText);
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


void Graphics::updateEntity(GraphicalEntity *entity, const float deltaTime, const QPointF &position)
{
	entity->setDirection(static_cast<BS::Graphic::Direction>(
		camera->discretizeAngle(physicsEngine->getAngle(entity->getObject()))));
	entity->setPosition(position);
	entity->update(deltaTime);
}


QPointF Graphics::getPosition(GraphicalEntity *entity) const
{
	return camera->getPerspective()->fromMetresToPixels(physicsEngine->getPosition(entity->getObject()));
}


void Graphics::addEffect(const QString &effectName, Effect *effect, std::list<std::pair<QString, Effect *>> &effectsList)
{
	int id = effect->getOrderId();
	auto elem = std::make_pair("BasePolygons", effect);
	for (auto it = effectsList.begin(); it != effectsList.end(); ++it) {
		if (it->second->getOrderId() > id) {
			effectsList.insert(it, elem);
			return;
		}
	}

	effectsList.push_back(elem);
}


bool Graphics::removeEffect(const QString &effectName, std::list<std::pair< QString, Effect *>> &effectsList)
{
	for (auto it = effectsList.begin(); it != effectsList.end(); ++it) {
		if (it->first == effectName) {
			delete it->second;
			effectsList.erase(it);
			return true;
		}
	}

	return false;
}


void Graphics::drawRubberBand()
{
	if (widget->isRubberBandVisible()) {
		QRectF rect = widget->rubberBandRect();
		rubberBand.setPosition(rect.left(), rect.top());
		rubberBand.setSize(sf::Vector2f(rect.width(), rect.height()));
		widget->draw(rubberBand);
	}
}

