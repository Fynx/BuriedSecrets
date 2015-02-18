/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/SelectionEffect.hpp"

#include "Common/Geometry.hpp"
#include "Common/Strings.hpp"


SelectionEffect::SelectionEffect() : Effect{}
{
	circleShape.setPointCount(20);
	circleShape.setFillColor(sf::Color::Transparent);
	circleShape.setOutlineColor(sf::Color::Cyan);
	circleShape.setOutlineThickness(1);
}


void SelectionEffect::draw(const GraphicalEntity *graphicalEntity, const QPointF &entityPosition,
			   const Viewport *viewport, sf::RenderTarget *renderTarget)
{
	const Object *obj = graphicalEntity->getObject();
	if (obj->property(TempData::IsSelected).toBool()) {
		auto objType = obj->getPrototype()->getProperty("type").toString();
		float radiusPx = 0.0f;
		QPointF scale = viewport->getWholeScale();

		if (objType == "unit") {
			float radius = obj->getPrototype()->getProperty("baseRadius").toFloat();
			radiusPx = std::min(radius * scale.x(), radius * scale.y()) * 1.5f;
		} else {
			QPointF centre = graphicalEntity->getBaseCentre();
			basePolygon = graphicalEntity->getBasePolygon();
			for (const QPointF &p: basePolygon) {
				radiusPx = std::max(radiusPx, BS::Geometry::distance(p, centre));
				qDebug() << radiusPx;
			}
		}

		// FIXME this whole scale mumbo-jumbo might need to be reworked here.
		// Selections work fine for now.
		scale /= std::min(scale.x(), scale.y());
		circleShape.setScale(scale.x(),  scale.y());
		float maxNormScale = std::max(scale.x(), scale.y());

		QPointF radiusDelta{radiusPx * scale.x() / maxNormScale, radiusPx * scale.y() / maxNormScale};

		QPointF position = entityPosition - 2 * radiusDelta;
		circleShape.setPosition(position.x(), position.y());
		circleShape.setRadius(radiusPx);
		renderTarget->draw(circleShape);
	}
}


int SelectionEffect::getOrderId() const
{
	return BS::Graphic::EffectOrder::Selection;
}
