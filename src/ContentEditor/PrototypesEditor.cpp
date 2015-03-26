/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Common/Strings.hpp"
#include "ContentEditor/PrototypesEditor.hpp"

PrototypesEditor::PrototypesEditor(QWidget *parent, DataManager *dataManager)
	: QWidget(parent),
	  dataManager(dataManager)
{
	prototypesList = new QListWidget();
	connect(prototypesList, &QListWidget::itemActivated, this, &PrototypesEditor::onItemSelected);

	stats = new QTableWidget();
	connect(stats, &QTableWidget::cellChanged, this, &PrototypesEditor::onFieldChanged);

	initLayout();
	updateList();
}

PrototypesEditor::~PrototypesEditor()
{}

void PrototypesEditor::initLayout()
{
	QHBoxLayout *layout = new QHBoxLayout();

	layout->addWidget(prototypesList);


	QVBoxLayout *layoutStats = new QVBoxLayout();

	stats->setColumnCount(2);
	stats->setColumnWidth(0, 200.0);
	stats->setColumnWidth(1, 400.0);
	layoutStats->addWidget(stats);

	layout->addItem(layoutStats);


	setLayout(layout);
}

void PrototypesEditor::updateList()
{
	prototypesList->clear();

	prototypes = dataManager->getPrototypesMap();

	for (const Prototype *p : prototypes)
		prototypesList->addItem(p->getProperty(Properties::Name).toString());
}

void PrototypesEditor::onItemSelected()
{
	settingValues = true;

	stats->clear();
	stats->setRowCount(0);
	stats->setHorizontalHeaderLabels({"Keys", "Values"});
	int counter = 0;
	for (const QString &key : getCurrentPrototype()->getProperties().keys()) {
		QTableWidgetItem *itemKey = new QTableWidgetItem(key);
		QTableWidgetItem *itemVal = new QTableWidgetItem(QString(getCurrentPrototype()->getProperty(key).toByteArray()));
		stats->insertRow(counter);
		stats->setItem(counter, 0, itemKey);
		stats->setItem(counter, 1, itemVal);
		keys[counter] = key;
		values[key] = getCurrentPrototype()->getProperty(key);
		++counter;
	}

	settingValues = false;
}

void PrototypesEditor::onFieldChanged(int row, int col)
{
	if (settingValues)
		return;

	if (stats->currentColumn() != col || stats->currentRow() != row) {
		err("PrototypesEditor: invalid row or column.");
		return;
	}

	if (col == 0) {
		QString oldKey = keys[row];
		QString newKey = stats->item(row, col)->text();

		qDebug() << "changing key from" << oldKey << "to" << newKey;

		QVariant value = values[oldKey];

		values.remove(oldKey);
		values.insert(newKey, value);
		getCurrentPrototype()->removeProperty(oldKey);
		getCurrentPrototype()->setProperty(newKey, value);
		keys[row] = newKey;
	} else if (col == 1) {
		QVariant newValue = QVariant(stats->item(row, col)->text());
		qDebug() << "changing value" << keys[row] << "from"
			<< getCurrentPrototype()->getProperty(keys[row]) << "to" << newValue;

		values[keys[row]] = newValue;
		getCurrentPrototype()->setProperty(keys[row], newValue);
	} else {
		err("Invalid column in PrototypesEditor.");
	}
}

Prototype *PrototypesEditor::getCurrentPrototype()
{
	return prototypes[prototypesList->currentItem()->text()];
}
