/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/Viewport.hpp"


Viewport::Viewport(const Perspective *perspective)
	: perspective{perspective}, currentView{0, 0, 0, 0}
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
	return point * scale;
}


void Viewport::setViewSize(const float viewWidth, const float viewHeight)
{
	this->viewWidth = viewWidth;
	this->viewHeight = viewHeight;
	updateView();
}


void Viewport::setMapSize(const float mapWidth, const float mapHeight)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	updateView();
}


void Viewport::setScale(const float scale)
{
	const float oldScale = this->scale;
	const float reScale = sqrt(oldScale / scale);
	this->scale = scale;

	currentView = QRectF(currentView.topLeft() * reScale, currentView.bottomRight() * reScale);
	updateView();
}


void Viewport::updateView()
{
	// QPointF topLeft = currentView.topLeft();
	// TODO
	// calculate the rect based on perpective, viewWidth, viewHeight, map and scale
}

