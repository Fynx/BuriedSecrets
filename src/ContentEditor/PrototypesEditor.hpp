/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "DataManager/DataManager.hpp"

class PrototypesEditor : public QWidget {
Q_OBJECT;

public:
	PrototypesEditor(QWidget *parent, DataManager *dataManager);
	virtual ~PrototypesEditor();

private:
	void initLayout();

	void updateList();

	void onItemSelected();
	void onFieldChanged(int row, int col);
	void onAddRow();
	void onRemoveRow();

	Prototype *getCurrentPrototype();

	QListWidget *prototypesList;
	QTableWidget *stats;
	QPushButton *buttonAddRow;
	QPushButton *buttonRemoveRow;
	QHash<QString, Prototype *> prototypes;
	QHash<QString, QVariant> values;
	QHash<int, QString> keys;

	/** small hack */
	bool settingValues;

	DataManager *dataManager;
};