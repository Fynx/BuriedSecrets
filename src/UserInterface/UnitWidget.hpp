/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

static const QSize WidgetSize{200, 100};

class UnitWidget : public QFrame {
public:
	UnitWidget();
	QSize sizeHint() const;

private:
	void initWidgets();
	void initLayout();

	QPushButton *face_;
	QLabel *name_;

};
