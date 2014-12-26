/*
 { { *license|lines_prepend:" * " }}
 */
#pragma once

#include <QtWidgets>

class DataManager;

class InterfaceDataManager {

public:
	InterfaceDataManager(const DataManager *dataManager);
	~InterfaceDataManager();

	const QImage * getImage(const QString &name);

private:
	const DataManager *dataManager_;
	QHash<QString, QImage *> images_;
};
