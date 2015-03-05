/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "Common/Enums.hpp"

class SlotWidget : public QFrame {

public:
	SlotWidget(BS::Slot slot);
	SlotWidget(BS::Slot slot, QPixmap pixmap, const QString &text, int itemUid);

	void setItem(const QPixmap &pixmap, const QString &text, int itemUid);
	void markEnabled(bool enabled);
	void markLinked(bool linked);

	BS::Slot slot() const;
	int itemUid() const;

private:
	static const QSize MiniatureSize;
	void initLayout();

	BS::Slot slot_;
	QLabel *miniature_;
	QLabel *text_;
	int itemUid_;
};
