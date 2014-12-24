/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "UserInterface/Perspective.hpp"

/**
 * @brief This class represents the viewport.
 *
 * It knows and can give information about what area (in the logical coordinates) of the world is the current
 * viewport including:
 *  - scale,
 *  - position of the viewport,
 *  - perspective.
 *
 * TODO there probably will be more methods for this class in the future.
 */
class Viewport {
public:
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
	QPointF getScaledPoint(const QPointF& point) const;

	void setViewSize(const float viewWidth, const float viewHeight);
	void setMapSize(const float mapWidth, const float mapHeight);
	void setScale(const float scale);
// 	void moveToLogicalCoordinates

private:
	void updateView();

	const Perspective *perspective;
	float scale;
	float mapWidth;
	float mapHeight;
	float viewWidth;
	float viewHeight;
	QRectF currentView;
};