/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Mind;
class UnitWidget;

class UnitsPanel : public QFrame {
	Q_OBJECT
public:
	UnitsPanel();
	QSize sizeHint() const;
	void refresh(const Mind *mind);

private:
	QList <UnitWidget *> unitWidgets_;
	QSignalMapper signalMapper_;

signals:
	void sizeChanged();
	void unitSelected(int uid);
};
