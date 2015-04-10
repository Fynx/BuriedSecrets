/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "Common/Enums.hpp"

class Mind;
class DataManager;
class JournalEntryWidget;

class JournalWindow : public QFrame {
	Q_OBJECT
public:
	JournalWindow(Mind *m, DataManager *dm);

	void refresh();
	void setCurrentEntry(int uid);

private:
	static const QFont LabelsFont;
	static const QString FilterAll;
	static const QMap<QString, QSet<BS::EntryType>> Filters;

	void initLayout();
	QLayout *createFiltersButtons();

	Mind *mind_;
	DataManager *dataManager_;

	QListWidget *entriesList_;
	JournalEntryWidget *journalEntryWidget_;

	QString currentFilter_;
	QSignalMapper filtersMapper_;
	QHash<QString, QPushButton *> filters_;

	QPushButton *closeBtn_;

private slots:
	void onFilterClicked(const QString &filterName);
	void onCurrentEntryChanged(QListWidgetItem *item);

signals:
	void exit();
};
