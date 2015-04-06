/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

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
	void initLayout();

	Mind *mind_;
	DataManager *dataManager_;

	QListWidget *entriesList_;
	JournalEntryWidget *journalEntryWidget_;
	QPushButton *closeBtn_;

private slots:
	void onCurrentEntryChanged(QListWidgetItem *item);

signals:
	void exit();
};
