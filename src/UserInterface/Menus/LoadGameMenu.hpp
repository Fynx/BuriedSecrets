/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

/**
 * UI menu to load previously saved games.
 */
class LoadGameMenu : public QWidget {
	Q_OBJECT
public:
	LoadGameMenu(QWidget *parent = nullptr);
    void refreshList();

private:
	static const QMargins ContentsMargins;

	void initLayout();
	QWidget *createSavesList();
	QWidget *createCloseBtn();

	QListWidget *savesList_;

private slots:
	void onSaveDoubleClicked(const QModelIndex &index);

signals:
	void closeActivated();
	void loadGame(QString path);
};
