/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/Viewport/Viewport.hpp"

#include <QDebug>
#include "UserInterface/Viewport/Perspective.hpp"

Viewport::Viewport(const Perspective *perspective)
	: perspective{perspective},
	  zoom{1.0f},
	  mapSize{0,0},
	  currentView{0, 0, 0, 0}
{}


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


QPointF Viewport::fromMetresToPixels(const QPointF &pointInMetres) const
{
	return perspective->fromMetresToPixels(pointInMetres);
}


QPointF Viewport::fromPixelsToMetres(const QPointF &pointInPixels) const
{
	return perspective->fromPixelsToMetres(pointInPixels);
}


QPointF Viewport::getScreenCoordinates(const QPointF &physicalPoint) const
{
	return fromMetresToPixels(physicalPoint - currentView.topLeft());
}


QPointF Viewport::getPhysicalCoordinates(const QPointF &screenPoint) const
{
	return fromPixelsToMetres(screenPoint) + currentView.topLeft();
}


QPointF Viewport::getScaledPoint(const QPointF &point) const
{
	return point * zoom;
}


QPointF Viewport::getWholeScale() const
{
	QPointF p{1.0f, 1.0f};
	return getScaledPoint(fromMetresToPixels(p));
}


void Viewport::moveViewInMetres(QPointF deltaInMetres)
{
	currentView.translate(deltaInMetres);
	updateView();
}


void Viewport::moveViewInPixels(const QPoint &deltaInPixels)
{
	moveViewInMetres(perspective->fromPixelsToMetres(deltaInPixels));
}


void Viewport::setViewSizeInMetres(const QSizeF &sizeInMetres)
{
	auto currentCenter = currentView.center();
	currentView.setSize(sizeInMetres);
	currentView.moveCenter(currentCenter);
	updateView();
}


void Viewport::setViewSizeInPixels(const QSize &sizeInPixels)
{
	QSizeF sizeInMetres = perspective->fromPixelsToMetres(sizeInPixels);
	setViewSizeInMetres(sizeInMetres);
}


void Viewport::centerOnPointInMetres(const QPointF &point)
{
	currentView.moveCenter(point);
	updateView();
}


void Viewport::setMapSize(const QSizeF &mapSize)
{
	this->mapSize = mapSize;
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


float Viewport::getZoom() const
{
	return zoom;
}


void Viewport::updateView()
{
	currentView = viewWithinMap(currentView);
}


QRectF Viewport::viewWithinMap(QRectF newView)
{
	qreal deltaLeft = qMax(0.0, newView.right() - mapSize.width());
	qreal deltaUp = qMax(0.0, newView.bottom() - mapSize.height());
	newView.translate((-1) * deltaLeft, (-1) * deltaUp);

	qreal deltaRight = qMax(0.0, 0 - newView.left());
	qreal deltaDown = qMax(0.0, 0 - newView.top());
	newView.translate(deltaRight, deltaDown);

	return newView;
}


QDebug operator<< (QDebug d, const Viewport &viewport) {
	d << "Viewport(";
		d << "View(" << viewport.getCurrentView() <<")";
	d << ")";
	return d;
}
