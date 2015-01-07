/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "UserInterface/Perspective.hpp"

/**
 * @brief This class represents the viewport.
 *
 * It knows and can give information about what area (in the logical coordinates) of the world the current
 * viewport is, including:
 *  - scale,
 *  - position of the viewport,
 *  - perspective.
 *
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
	QString toString() const;

	void moveViewInPixels(const QPointF &deltaInPixels);
	void moveViewInMetres(const QPointF &deltaInMetres);
	void setViewSizeInMetres(const QSizeF &sizeInMetres);
	void setViewSizeInPixels(const QSizeF &sizeInPixels);
	/**
	 * @brief Sets the map size. Arguments are in metres.
	 */
	void setMapSize(const float mapWidth, const float mapHeight);
	void setZoom(const float zoom);
	void resetZoom();
	void zoomIn(qreal zoomDelta);

private:
	void updateView();

	const Perspective *perspective;
	float zoom;
	float mapWidth;
	float mapHeight;
	float viewWidth;
	float viewHeight;
	QRectF currentView;
};
