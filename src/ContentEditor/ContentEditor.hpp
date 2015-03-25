/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "ContentEditor/PrototypesEditor.hpp"
#include "DataManager/DataManager.hpp"

class ContentEditor : public QWidget {
Q_OBJECT;

public:
	ContentEditor();
	virtual ~ContentEditor();

private:
	void initObjects();
	void initLayout();

	void onSave();
	void onQuit();

	virtual void keyPressEvent(QKeyEvent *event);

	QTabWidget *tabWidget;
	PrototypesEditor *prototypesEditor;

	QPushButton *buttonSave;
	QPushButton *buttonQuit;

	DataManager *dataManager;
};