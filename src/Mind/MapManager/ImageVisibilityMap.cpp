/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/MapManager/ImageVisibilityMap.hpp"

#include <QImage>
#include <QPainter>

#include "GameObjects/Object.hpp"
#include "Mind/MapManager/VisibilityUpdate.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"


ImageVisibilityMap::ImageVisibilityMap(const QSize &size)
		: mapImage{size, QImage::Format_ARGB32_Premultiplied}
{
	clear();
}


void ImageVisibilityMap::update(const VisibilityUpdate &visibilityUpdate)
{
	QPainter painter;
	QColor includeColor = Qt::transparent;
	QColor ommitColor = Qt::black;

	// Resize tempImage only when needed.
	if ((tempImage.width() < visibilityUpdate.includeCircle.radius * 2) ||
		(tempImage.height() < visibilityUpdate.includeCircle.radius * 2)) {
		tempImage = QImage{QSize{(int)(visibilityUpdate.includeCircle.radius * 2),
			(int)(visibilityUpdate.includeCircle.radius * 2)},
			QImage::Format_ARGB32_Premultiplied};
	}
	tempImage.fill(ommitColor);

	painter.begin(&tempImage);

	painter.setBrush(QBrush{includeColor});
	painter.setPen(QPen{includeColor});
	painter.setCompositionMode(QPainter::CompositionMode_Source);

	painter.drawEllipse(0, 0, visibilityUpdate.includeCircle.radius * 2, visibilityUpdate.includeCircle.radius * 2);

	painter.setBrush(QBrush{ommitColor});
	painter.setPen(QPen{ommitColor});
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);


	for (const auto &poly: visibilityUpdate.ommitPolygons) {
		QPolygonF realPoly = poly;

		for (QPointF &point: realPoly) {
			point -= (visibilityUpdate.includeCircle.centre -
					QPointF{visibilityUpdate.includeCircle.radius,
						visibilityUpdate.includeCircle.radius});
		}

		painter.drawPolygon(realPoly);
	}

	painter.end();
	painter.begin(&mapImage);

	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	painter.drawImage(visibilityUpdate.includeCircle.centre -
			QPointF{visibilityUpdate.includeCircle.radius, visibilityUpdate.includeCircle.radius},
			tempImage);
	painter.end();
}


bool ImageVisibilityMap::isVisible(const QPointF &point) const
{
	if (!mapImage.rect().contains(point.toPoint())) {
		return false;	// Cannot see outside the map.
	}
	return qAlpha(mapImage.pixel(point.toPoint())) < 255;
}


void ImageVisibilityMap::clear()
{
	mapImage.fill(Qt::black);
}


bool ImageVisibilityMap::isVisible(const Unit *from, const QPointF &target, const Object *owner,
				   const PhysicsEngine *physicsEngine) const
{
	// We ignore from (assuming it belongs to this map).
	return isVisible(target);
}


