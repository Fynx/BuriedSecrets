/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/BoardWidget.hpp"

BoardWidget::BoardWidget()
	: isRubberBandVisible_(false)
{}

QRect BoardWidget::rubberBandRect() const
{
	return rubberBandRect_.normalized();
}

bool BoardWidget::isRubberBandVisible() const
{
	if (isRubberBandVisible_) {
		if (qMax(rubberBandRect_.width(), rubberBandRect_.height()) < MinimalRectSize)
			return false;
	}
	return isRubberBandVisible_;
}

void BoardWidget::mousePressEvent(QMouseEvent *event)
{

	if (!(event->buttons() & Qt::LeftButton)) {
		QWidget::mousePressEvent(event);
		return;
	}

	isRubberBandVisible_ = true;
	rubberBandRect_ = QRect(event->pos(), QSize());

	QWidget::mousePressEvent(event);
}

void BoardWidget::mouseMoveEvent(QMouseEvent *event)
{
	rubberBandRect_.setBottomRight(event->pos());
}

void BoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (!(event->button() == Qt::LeftButton)) {
		QWidget::mousePressEvent(event);
		return;
	}

	isRubberBandVisible_ = false;

	emit selectionEnded(rubberBandRect());

	QWidget::mousePressEvent(event);
}
