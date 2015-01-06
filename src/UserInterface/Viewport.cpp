/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/Viewport.hpp"
#include <QDebug>

Viewport::Viewport(const Perspective *perspective)
	: perspective{perspective}, zoom{1.0f}, currentView{0, 0, 0, 0}
{
	mapWidth = mapHeight = viewWidth = viewHeight = 0;
}


Viewport::~Viewport()
{
	delete perspective;
}


const Perspective * Viewport::getPerspective() const
{
	return perspective;
}


QRectF Viewport::getCurrentView() const
{
	return currentView;
}


QPointF Viewport::getScaledPoint(const QPointF &point) const
{
	return point * zoom;
}


QString Viewport::toString() const
{
	return (QString("Viewport: ") +
	        QString("\nMap: ") + QString::number(mapWidth) + QString("x") + QString::number(mapHeight) +
	        QString("\nView: ") + QString::number(viewWidth) + QString("x") + QString::number(viewHeight) +
	        QString("\nZoom: ") + QString::number(zoom));
}


void Viewport::moveViewInMeters(const QPointF &deltaInMeters)
{
	// what TODO?
}


void Viewport::moveViewInPixels(const QPointF &deltaInPixels)
{
	//what TODO?
}


void Viewport::setViewSizeInMeters(const QSizeF &sizeInMeters)
{
	viewWidth = sizeInMeters.width();
	viewHeight = sizeInMeters.height();
	updateView();
}


void Viewport::setViewSizeInPixels(const QSizeF &sizeInPixels)
{
	QSizeF sizeInMeters = perspective->fromPixelsToMeters(sizeInPixels);
	viewWidth = sizeInMeters.width();
	viewHeight = sizeInMeters.height();
	updateView();
}


void Viewport::setMapSize(const float mapWidth, const float mapHeight)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	updateView();
}


void Viewport::setZoom(const float zoom)
{
	const float oldZoom = this->zoom;
	const float reZoom = sqrt(oldZoom / zoom);
	this->zoom = zoom;

	currentView = QRectF(currentView.topLeft() / reZoom, currentView.bottomRight() * reZoom);
	updateView();
}


void Viewport::resetZoom()
{
	zoom = 1.0f;
	//TODO?
}


void Viewport::zoomIn(qreal zoomDelta)
{
	zoom += zoomDelta;
	//TODO?
}


void Viewport::updateView()
{
	QPointF topLeft = currentView.topLeft();
	float finalWidth = viewWidth * zoom;
	float finalHeight = viewHeight * zoom;
	currentView = perspective->getLogicalRect(QRectF{
		topLeft,
		QPointF{topLeft.x() + finalWidth, topLeft.y() + finalHeight}}
	);
// 	FIXME don't allow the rect to go beyond the map
}
