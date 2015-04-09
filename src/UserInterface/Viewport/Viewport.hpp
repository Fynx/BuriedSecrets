/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtCore>

class Perspective;

/**
 * @brief This class represents the viewport.
 *
 * It knows and can give information about what area (in the logical coordinates) of the world the current
 * viewport is, including:
 *  - scale,
 *  - position of the viewport,
 *  - perspective.
 */
class Viewport {
public:
	/**
	 * @brief The class takes ownership of the perspective.
	 */
	Viewport(const Perspective *perspective);
	~Viewport();

	// Copy is deleted, because I don't know how to do it right.
	// Will think on it if needed, otherwise don't care.
	Viewport(const Viewport &other) = delete;
	Viewport(Viewport && other) = default;

	Viewport &operator=(const Viewport &other) = delete;
	Viewport &operator=(Viewport && other) = default;

	const Perspective *getPerspective() const;
	/**
	 * @brief Returns the logical coordinates of the current area the player should see.
	 */
	QRectF getCurrentView() const;
	QPointF getScaledPoint(const QPointF &point) const;
	// The two following methods return the point scaled.
	QPointF fromPixelsToMetres(const QPointF &pointInPixels) const;
	QPointF fromMetresToPixels(const QPointF &pointInMetres) const;
	// The two following methods return the point scaled and moved so that it corresponds to the actual screen
	// coordinates of the point.
	QPointF getScreenCoordinates(const QPointF &physicalPoint) const;
	QPointF getPhysicalCoordinates(const QPointF &screenPoint) const;
	/**
	 * @brief Returns the whole scale from metres to pixels including zoom.
	 */
	QPointF getWholeScale() const;

	void moveViewInPixels(const QPoint &deltaInPixels);
	void moveViewInMetres(QPointF deltaInMetres);
	void setViewSizeInMetres(const QSizeF &sizeInMetres);
	void setViewSizeInPixels(const QSize &sizeInPixels);
	void centerOnPointInMetres(const QPointF &point);
	/**
	 * @brief Sets the map size. Arguments are in metres.
	 */
	void setMapSize(const QSizeF &mapSize);
	void setZoom(const float zoom);
	void resetZoom();
	void zoomIn(qreal zoomDelta);
	float getZoom() const;

private:
	void updateView();
	QRectF viewWithinMap(QRectF newView);

	const Perspective *perspective;
	float zoom;
	QSizeF mapSize;
	QRectF currentView;
};

QDebug operator<< (QDebug d, const Viewport &viewport);
