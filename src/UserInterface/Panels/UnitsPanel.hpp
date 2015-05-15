/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Mind;
class UnitSection;

	enum class UnitStatus {
		Member,
		Psycho,
		Dead
	};

/**
 * Widget to display info about player's units.
 * Contains IconsSections or UnitsSections.
 */
class UnitsPanel : public QFrame {
	Q_OBJECT
public:
	static const QSize SectionSize;

	UnitsPanel(DataManager *dataManager, const Mind *mind);
	QSize sizeHint() const;
	void refresh();

public slots:
	void setSelection(int uid, bool isSelected);

private:
	bool didUnitsChange();
	void rebuild();
	void appendUnitSection(int uid);
	UnitStatus determineUnitStatus(int uid);

	DataManager *const dataManager_;
	const Mind *const mind_;

	QList<QPair<int, UnitStatus>> unitsStates_; //id, isAlive
	QHash<int, UnitSection *> unitSections_;
	QHBoxLayout *panelLayout_;

	QSignalMapper pickSignalMapper_;
	QSignalMapper showMenuSignalMapper_;
	QSignalMapper showUnitSignalMapper_;


signals:
	void pickUnit(int uid);
	void showUnit(int uid);
	void showUnitMenu(int uid);

	void sizeChanged();
};
