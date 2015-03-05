/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "Common/Enums.hpp"

class SlotWidget : public QFrame {
	Q_OBJECT

public:
	SlotWidget(BS::Slot slot);
	SlotWidget(BS::Slot slot, QPixmap pixmap, const QString &text, int itemUid);

	void setItem(const QPixmap &pixmap, const QString &text, int itemUid);
	void clearItem();

	void markEnabled(bool enabled);
	void markLinked(bool linked);

	BS::Slot slot() const;
	int itemUid() const;

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

private:
	static const QSize MiniatureSize;

	void initLayout();
	void performDrag();

	QPoint dragStartPos_;

	BS::Slot slot_;
	QLabel *miniature_;
	QLabel *text_;
	int itemUid_;

signals:
	void itemLinkedIn(BS::Slot slot, int uid);
	void itemLinkedOut(BS::Slot slot, int uid);
};
