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

	buttonAddRow = new QPushButton("Add row");
	connect(buttonAddRow, &QPushButton::clicked, this, &PrototypesEditor::onAddRow);
	buttonRemoveRow = new QPushButton("Remove row");
	connect(buttonRemoveRow, &QPushButton::clicked, this, &PrototypesEditor::onRemoveRow);

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

	QHBoxLayout *layoutButtons = new QHBoxLayout();
	layoutButtons->addWidget(buttonRemoveRow);
	layoutButtons->addItem(new QSpacerItem(50, 50));
	layoutButtons->addWidget(buttonAddRow);

	layoutStats->addItem(layoutButtons);


	layout->addItem(layoutStats);


	setLayout(layout);
}

void PrototypesEditor::updateList()
{
	prototypesList->clear();

	prototypes = dataManager->getPrototypesMap();

	QStringList keys = prototypes.keys();
	qSort(keys.begin(), keys.end());

	for (const QString &key : keys)
		prototypesList->addItem(key);
}

void PrototypesEditor::onItemSelected()
{
	settingValues = true;

	stats->clear();
	stats->setRowCount(0);
	stats->setHorizontalHeaderLabels({"Keys", "Values"});
	int counter = 0;

	QStringList keysList = getCurrentPrototype()->getProperties().keys();
	qSort(keysList.begin(), keysList.end());

	for (const QString &key : keysList) {
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

		if (newKey.isEmpty()) {
			warn("The key is empty!");
			return;
		}

		qDebug() << "changing key from" << oldKey << "to" << newKey;

		QVariant value;
		if (values.contains(oldKey)) {
			value = values[oldKey];
			values.remove(oldKey);
			getCurrentPrototype()->removeProperty(oldKey);
		} else {
			if (stats->item(row, 1) != nullptr)
				value = stats->item(row, 1)->text();
		}

		values.insert(newKey, value);

		getCurrentPrototype()->setProperty(newKey, value);
		keys[row] = newKey;
	} else if (col == 1) {
		if (!keys.contains(row)) {
			qDebug() << "Edited value, but not the key.";
			return;
		}

		QVariant newValue = QVariant(stats->item(row, col)->text());
		qDebug() << "changing value" << keys[row] << "from"
			<< getCurrentPrototype()->getProperty(keys[row]) << "to" << newValue;

		values[keys[row]] = newValue;
		getCurrentPrototype()->setProperty(keys[row], newValue);
	} else {
		err("Invalid column in PrototypesEditor.");
	}
}

void PrototypesEditor::onAddRow()
{
	if (getCurrentPrototype() == nullptr)
		return;
	stats->insertRow(stats->rowCount());
}

void PrototypesEditor::onRemoveRow()
{
	if (getCurrentPrototype() == nullptr)
		return;

	int row = stats->currentRow();

	qDebug() << "remove row" << keys[row];

	getCurrentPrototype()->removeProperty(keys[row]);
	values.remove(keys[row]);
	keys.remove(row);
	stats->removeRow(row);
}

Prototype *PrototypesEditor::getCurrentPrototype()
{
	if (prototypesList->currentItem() == nullptr)
		return nullptr;
	return prototypes[prototypesList->currentItem()->text()];
}
