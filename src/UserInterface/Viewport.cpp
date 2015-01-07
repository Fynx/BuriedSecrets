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


const Perspective *Viewport::getPerspective() const
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


void Viewport::moveViewInMetres(const QPointF &deltaInMetres)
{
	currentView = QRectF{currentView.topLeft() + deltaInMetres, currentView.bottomRight() + deltaInMetres};
}


void Viewport::moveViewInPixels(const QPointF &deltaInPixels)
{
	moveViewInMetres(perspective->fromPixelsToMetres(deltaInPixels));
}


void Viewport::setViewSizeInMetres(const QSizeF &sizeInMetres)
{
	viewWidth = sizeInMetres.width();
	viewHeight = sizeInMetres.height();
	updateView();
}


void Viewport::setViewSizeInPixels(const QSizeF &sizeInPixels)
{
	QSizeF sizeInMetres = perspective->fromPixelsToMetres(sizeInPixels);
	viewWidth = sizeInMetres.width();
	viewHeight = sizeInMetres.height();
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
// 	float finalWidth = viewWidth * zoom;
// 	float finalHeight = viewHeight * zoom;
	currentView = QRectF(topLeft, QPointF(topLeft.x() + viewWidth, topLeft.y() + viewHeight));
// 	FIXME don't allow the rect to go beyond the map
}
