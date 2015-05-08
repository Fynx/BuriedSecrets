/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/MapManager/PrecomputedAccessibilityMap.hpp"

#include <QImage>

#include "Common/Strings.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/MapManager/MapManager.hpp"


PrecomputedAccessibilityMap::PrecomputedAccessibilityMap(const MapManager *mapManager, const int gridSize,
							 const Unit *unit)
	: AccessiblityMap{mapManager, gridSize}, unit{unit}
{
	QSizeF size = mapManager->getMap()->getSize();
	QPoint sizeP = discretize(QPointF{size.width(), size.height()});
	width = sizeP.x() + 1;
	height = sizeP.y() + 1;

	matrix = new bool*[width];
	for (int i = 0; i < width; ++i) {
		matrix[i] = new bool[height];
		for (int j = 0; j < height; ++j) {
			matrix[i][j] = mapManager->canStandOn(unit, undiscretize(QPoint{i, j}));
		}
	}

        // Debug
// 	QSizeF mapSize = mapManager->getMap()->getSize();
// 	QImage image{mapSize.toSize(), QImage::Format_ARGB32};
// 	image.fill(Qt::transparent);
// 	QPainter painter{&image};
// 	painter.setBrush(QBrush(Qt::black));
//
// 	for (int x = 0; x < width; ++x) {
// 		for (int y = 0; y < height; ++y) {
// 			if (!matrix[x][y]) {
// 				painter.drawRect(x * gridSize, y * gridSize, gridSize, gridSize);
// 			}
// 		}
// 	}
//
// 	qDebug() << unit->getName();
// 	image.save("/tmp/" + unit->getName() + ".png");
	// End of Debug
}


PrecomputedAccessibilityMap::~PrecomputedAccessibilityMap()
{
	for (int i = 0; i < width; ++i) {
		delete[] matrix[i];
	}

	delete[] matrix;
}


bool PrecomputedAccessibilityMap::isAccessible(const Unit *unit, const QPoint &point)
{
	assert(point.x() >= 0 && point.x() < width && point.y() >= 0 && point.y() < height);
	return matrix[point.x()][point.y()];
}


void PrecomputedAccessibilityMap::addObject (const Object *object, const QPointF &position)
{
	const Prototype *prototype = object->getPrototype();
	if (prototype->hasProperty(Properties::BasePolygon)) {
		const auto basePolygon = prototype->getBasePolygon();
		const auto baseCentre = prototype->getBaseCentre();
		qreal xMin, xMax, yMin, yMax;
		xMin = xMax = basePolygon.first().x();
		yMin = yMax = basePolygon.first().y();
		for (const auto &p : basePolygon) {
			xMin = qMin(xMin, p.x());
			yMin = qMin(yMin, p.y());
			xMax = qMax(xMax, p.x());
			yMax = qMax(yMax, p.y());
		}

		xMin += position.x() - baseCentre.x();
		xMax += position.x() - baseCentre.x();
		yMin += position.y() - baseCentre.y();
		yMax += position.y() - baseCentre.y();


		qDebug() << xMin << xMax << yMin << yMax;

		for (int x = xMin; x < (int)ceil(xMax); ++x) {
			for (int y = yMin; y < (int)ceil(yMax); ++y) {
				QPoint disc = discretize(QPointF{(float)x, (float)y});
				if (disc.x() >= 0 && disc.x() < width && disc.y() >= 0 && disc.y() < height) {
					matrix[disc.x()][disc.y()] = mapManager->canStandOn(unit, undiscretize(disc));
				}
			}
		}

		// Debug
// 		QSizeF mapSize = mapManager->getMap()->getSize();
// 		QImage image{mapSize.toSize(), QImage::Format_ARGB32};
// 		image.fill(Qt::transparent);
// 		QPainter painter{&image};
// 		painter.setBrush(QBrush(Qt::black));
//
// 		for (int x = 0; x < width; ++x) {
// 			for (int y = 0; y < height; ++y) {
// 				if (!matrix[x][y]) {
// 					painter.drawRect(x * gridSize, y * gridSize, gridSize, gridSize);
// 				}
// 			}
// 		}
//
// 		qDebug() << unit->getName();
// 		image.save("/tmp/" + unit->getName() + ".png");
		// End of Debug
	}
}


void PrecomputedAccessibilityMap::removeObject(const Object *object, const QPointF &position) {
	addObject(object, position);
}


