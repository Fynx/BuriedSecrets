/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class SaveGameMenu : public QWidget {
	Q_OBJECT
public:
	SaveGameMenu(QWidget *parent = nullptr);

private:
	static const QMargins ContentsMargins;

	void initLayout();
	bool isFilenameValid(const QString &filename);
	QWidget *createSavesList();
	QWidget *createCloseBtn();
	QWidget *createNewBtn();

	QListWidget *savesList_;

private slots:
	void onSaveDoubleClicked(const QModelIndex &index);
	void onNewClicked();
	void askForName(const QString &name = {});

signals:
	void closeActivated();
	void saveGame(QString path);
};
