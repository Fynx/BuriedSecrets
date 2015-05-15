/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

/**
 * Widget used by (inherited by) Graphics module to draw game map on it.
 * That way whis widget can use Qt events to detect selections on map.
 */
class BoardWidget : public QWidget {
	Q_OBJECT

public:
	const int MinimalRectSize = 7;
	BoardWidget();

	QRect rubberBandRect() const;
	bool isRubberBandVisible() const;

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	QRect rubberBandRect_; // in pixels
	bool isRubberBandVisible_;

signals:
	void selectionEnded(QRect selectionRect);
};
