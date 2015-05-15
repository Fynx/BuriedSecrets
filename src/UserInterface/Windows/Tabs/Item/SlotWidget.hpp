/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "Common/Enums.hpp"

/**
 * Widget responsible for item's slots in units equipment.
 * Handles drag'n'drop.
 */
class UnitEquipmentTab;

class SlotWidget : public QFrame {
	Q_OBJECT

public:
	SlotWidget(UnitEquipmentTab *uet, BS::Slot slot);
	SlotWidget(UnitEquipmentTab *uet, BS::Slot slot, QPixmap pixmap, const QString &text, int itemUid);

	void setItem(const QPixmap &pixmap, const QString &text, int itemUid);
	void clearItem();

	void setMarked(bool isMarked);

	bool isEmpty() const;
	BS::Slot slot() const;
	int itemUid() const;

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);

	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

private:
	static const QSize MiniatureSize;

	void performDrag();
	void initLayout();

	QPoint dragStartPos_;

	UnitEquipmentTab *unitEquipmentTab_;
	BS::Slot slot_;
	QLabel *miniature_;
	QLabel *text_;
	int itemUid_;

signals:
	void slotActivated(int uid);
	void itemMovedIn(BS::Slot slot, int uid);
	void itemMovedOut(BS::Slot slot, int uid);
};
