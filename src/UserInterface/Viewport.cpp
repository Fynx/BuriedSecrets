/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/Viewport.hpp"
#include <QDebug>

Viewport::Viewport(const Perspective *perspective)
	: perspective{perspective}, zoom{1.0f}, currentView{0, 0, 0, 0}
{
	viewWidth = viewHeight = 0;
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
	QPointF newTopLeft = currentView.topLeft() + deltaInMetres;
	QPointF newBottomRight = currentView.bottomRight() + deltaInMetres;
	if (currentView.width() <= mapSize.width()) {
		// Excess to left.
		deltaInMetres.setX(deltaInMetres.x() + std::max(-newTopLeft.x(), 0.0));
		// Excess to right
		deltaInMetres.setX(deltaInMetres.x() - std::max(newBottomRight.x() - mapSize.width(), 0.0));
	}

	if (currentView.height() <= mapSize.height()) {
		// Excess up.
		deltaInMetres.setY(deltaInMetres.y() + std::max(-newTopLeft.y(), 0.0));
		// Excess down.
		deltaInMetres.setY(deltaInMetres.y() - std::max(newBottomRight.y() - mapSize.height(), 0.0));
	}

	currentView = QRectF{currentView.topLeft() + deltaInMetres, currentView.bottomRight() + deltaInMetres};
	updateView();
}


void Viewport::moveViewInPixels(const QPoint &deltaInPixels)
{
	moveViewInMetres(perspective->fromPixelsToMetres(deltaInPixels));
}


void Viewport::setViewSizeInMetres(const QSizeF &sizeInMetres)
{
	viewWidth = sizeInMetres.width();
	viewHeight = sizeInMetres.height();
	updateView();
}


void Viewport::setViewSizeInPixels(const QSize &sizeInPixels)
{
	QSizeF sizeInMetres = perspective->fromPixelsToMetres(sizeInPixels);
	setViewSizeInMetres(sizeInMetres);
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
	QPointF topLeft = currentView.topLeft();
// 	float finalWidth = viewWidth * zoom;
// 	float finalHeight = viewHeight * zoom;
	currentView = QRectF(topLeft, QPointF(topLeft.x() + viewWidth, topLeft.y() + viewHeight));
	if (currentView.width() > mapSize.width()) {
		// Center X in the view.
		qreal offset = (currentView.width() - mapSize.width()) / 2.0;
		currentView.setLeft(-offset);
		currentView.setRight(offset + mapSize.width());
	}

	if (currentView.height() > mapSize.height()) {
		// Center Y in the view.
		qreal offset = (currentView.height() - mapSize.height()) / 2.0;
		currentView.setTop(-offset);
		currentView.setBottom(offset + mapSize.height());
	}
}


QDebug operator<< (QDebug d, const Viewport &viewport) {
	d << "Viewport(";
		d << "View(" << viewport.getCurrentView() <<")";
	d << ")";
	return d;
}
