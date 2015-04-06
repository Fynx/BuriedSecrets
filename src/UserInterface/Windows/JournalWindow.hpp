/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Mind;
class DataManager;
class Journal;
class JournalEntryWidget;

class JournalWindow : public QFrame {
	Q_OBJECT
public:
	JournalWindow(Mind *m, DataManager *dm);

private:
	void initLayout();

	Mind *mind_;
	DataManager *dataManager_;
	Journal *journal_;

	QListWidget *entriesList_;
	JournalEntryWidget *journalEntryWidget_;
	QPushButton *closeBtn_;

signals:
	void exit();
};
