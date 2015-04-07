/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "Common/Enums.hpp"

class JournalEntry;
class Mind;

class AttitudeWidget : public QFrame {
	Q_OBJECT
public:
	AttitudeWidget(Mind *m);

public:
	void refresh(QSet<int> uids);

private:
	static const QFont TextFont;
	static const QSize IconSize;
	static const QSize WidgetSize;

	void initLayout();
	void setUnits(QSet<int> uids);
	bool inSameLocation(QSet<int> uids);
	bool anyUnitOutside(QSet<int> uids);
	void clearOptions();
	void addOption(BS::Attitude option);

	Mind *const mind_;
	QSet<int> uids_;
	QList<BS::Attitude> options_;
	bool outsideAttitudes_;

	QVBoxLayout *attitudeLayout_;
	QSignalMapper signalMapper_;

private slots:
	void onOptionClicked(int option);
};
