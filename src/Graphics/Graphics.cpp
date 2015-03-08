/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Graphics.hpp"

#include "Mind/ObjectEffectData.hpp"
#include "UserInterface/Perspective.hpp"


Graphics::Graphics(const PhysicsEngine *physicsEngine, const DataManager *dataManager, Mind *mind)
	: graphicsDataManager{dataManager}, showFPS{true}, showFOW{true}, timeElapsed{0.0f}, frames{0}
	, widget{new GraphicsWidget}, graphicalEntityFactory{nullptr}, physicsEngine{physicsEngine}
	, dataManager{dataManager}, mind{mind}, camera{nullptr}, mapSprite{nullptr}, drawOrder{new int[10000]}
	, FOW{nullptr}
{
	canvas = widget;
	fpsText.setFont(*graphicsDataManager.getFont("HEMIHEAD"));
	fpsText.setColor(sf::Color::Red);
	rubberBand.setFillColor(sf::Color{40, 200, 200, 127});
	rubberBand.setOutlineColor(sf::Color{50, 210, 210, 200});
	rubberBand.setOutlineThickness(1);
	widget->setVerticalSyncEnabled(true);
}


Graphics::~Graphics()
{
	delete mapSprite;
	mapSprite = nullptr;
	delete camera;
	delete drawOrder;
	delete FOW;
	delete graphicalEntityFactory;
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
	graphicalEntityFactory = new GraphicalEntityFactory{&graphicsDataManager, viewport};

	delete FOW;
	FOW = new GraphicalFogOfWar{canvas, mapManager, viewport};

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


void Graphics::loadMap()
{
	this->mapManager = mind->getMapManager();
	mapSprite = new sf::Sprite{*(graphicsDataManager.getTexture(mapManager->getMap()->getName()))};
	mapSprite->setPosition(0, 0);
}


void Graphics::toggleShowFPS()
{
	showFPS = !showFPS;
	clock.restart();
	timeElapsed = 0.0f;
	frames = 0;
}


void Graphics::toggleFogOfWar()
{
	showFOW = !showFOW;
}


void Graphics::render()
{
	canvas->clear(sf::Color::Black);
	canvas->setView(camera->getCurrentView());

	// Draw the map (can be a separate function).
	if (mapSprite != nullptr) {
		canvas->draw(*mapSprite);
	}

	// All the drawing logic for objects goes here.
	auto visibleObjects = camera->getVisibleObjects();

	if (showFOW) {
		// Filter out everything outside of FOW.
		for (int i = 0; i < visibleObjects.length(); ++i) {
			if (!mapManager->hasBeenSeen(visibleObjects[i])) {
				std::swap(visibleObjects[i], visibleObjects.back());
				visibleObjects.pop_back();
				--i;
			}
		}
	}

	auto visibleGraphicalEntities = getGraphicalEntitiesFor(visibleObjects);

	// This can be split out into separate function
	QSizeF mapSize = camera->getPerspective()->fromMetresToPixels(mind->getMap()->getSize());
	for (int i = 0; i < visibleGraphicalEntities.size(); ++i) {
		updateEntity(visibleGraphicalEntities[i], 0, getPosition(visibleGraphicalEntities[i]));
		QSizeF size = visibleGraphicalEntities[i]->getSizePx();
		QPointF pos = visibleGraphicalEntities[i]->getPosition();
		QPointF baseCentre = visibleGraphicalEntities[i]->getBaseCentre();
		pos -= baseCentre;	// Upper left corner of the texture.
		if (pos.x() + size.width() < 0.0 || pos.x() > mapSize.width() ||
			pos.y() + size.height() < 0.0 || pos.y() > mapSize.height()) {
			// The entity is outside map, remove it.
			std::swap(visibleGraphicalEntities[i], visibleGraphicalEntities.back());
			visibleGraphicalEntities.pop_back();
			--i;
		}
	}

	updateEffects(visibleGraphicalEntities);

	for (int i = 0; i < visibleGraphicalEntities.size(); ++i) {
		drawOrder[i] = i;
	}

	qSort(drawOrder, drawOrder + visibleGraphicalEntities.size(),
	      [&](const int &a, const int &b) -> bool {
		QPointF aP = visibleGraphicalEntities[a]->getPosition();
		QPointF bP = visibleGraphicalEntities[b]->getPosition();

		if (aP.y() != bP.y()) {
			return aP.y() < bP.y();
		}

		return aP.x() < bP.x();
	      });
	// End of separate function.

	GraphicalEntity *obj;

	// Draw pre effects.
	for (int i = 0, idx = drawOrder[0]; i < visibleGraphicalEntities.size(); idx = drawOrder[++i]) {
		obj = visibleGraphicalEntities[idx];
		visibleGraphicalEntities[idx]->drawPreEffects(canvas);
	}

	drawFOW();
	drawRubberBand();

	// Draw entities.
	for (int i = 0, idx = drawOrder[0]; i < visibleGraphicalEntities.size(); idx = drawOrder[++i]) {
		obj = visibleGraphicalEntities[idx];
		obj->draw(canvas);
	}

	// Draw post effects.
	for (int i = 0, idx = drawOrder[0]; i < visibleGraphicalEntities.size(); idx = drawOrder[++i]) {
		obj = visibleGraphicalEntities[idx];
		visibleGraphicalEntities[idx]->drawPostEffects(canvas);
	}

	drawFPS();

	// This call has to be at the end to repaint the widget.
	widget->repaint();
}


QVector<GraphicalEntity *> Graphics::getGraphicalEntitiesFor(const QList<const Object *> &objects)
{
	QVector<GraphicalEntity *> res;
	for (const auto& obj: objects) {
		res.append(graphicalEntityFactory->getOrCreate(obj));
	}
	return res;
}


void Graphics::updateEntity(GraphicalEntity *entity, const float deltaTime, const QPointF &position)
{
	entity->setPosition(position);
	entity->setDirection(static_cast<BS::Graphic::Direction>(
		camera->discretizeAngle(physicsEngine->getAngle(entity->getObject()))));
	entity->update(deltaTime);
}


QPointF Graphics::getPosition(GraphicalEntity *entity) const
{
	return camera->getPerspective()->fromMetresToPixels(physicsEngine->getPosition(entity->getObject()));
}


void Graphics::drawRubberBand()
{
	if (widget->isRubberBandVisible()) {
		QRectF rect = widget->rubberBandRect();
		QPointF offset = camera->getViewport()->fromMetresToPixels(
				camera->getViewport()->getCurrentView().topLeft());
		rubberBand.setPosition(rect.left() + offset.x(), rect.top() + offset.y());
		rubberBand.setSize(sf::Vector2f(rect.width(), rect.height()));
		widget->draw(rubberBand);
	}
}


void Graphics::drawFPS()
{
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
}


void Graphics::drawFOW()
{
	FOW->update();
	if (showFOW) {
		FOW->draw();
	}
}


void Graphics::updateEffects(QVector<GraphicalEntity *> &visibleEntities)
{
	// Get, filter and assign effects to entities.
	const auto *effects = mind->getActiveEffects();

	for (auto entity : visibleEntities) {
		entity->resetActiveEffects();
	}

	for (const Effect &effect : *effects) {
		const ObjectEffectData *objData = dynamic_cast<const ObjectEffectData *>(effect.getEffectData());

		if (objData == nullptr) {
			// Not an object effect - TODO
			EffectGraphicalEntity *effectEntity = graphicalEntityFactory->getOrCreateEffectEntity(effect);
			if (effectEntity != nullptr) {
				visibleEntities.append(effectEntity);
			}
		} else {
			GraphicalEntity *entity = graphicalEntityFactory->get(objData->getObject());
			if (entity == nullptr) {
				// We don't care, we don't have that entity in our Graphical memory anywhere.
				continue;
			}

			entity->addOrMarkEffectActive(effect);
		}
	}

	// Remove unused effects from all reset entities.
	for (auto entity : visibleEntities) {
		entity->removeInactiveEffects();
	}
}

