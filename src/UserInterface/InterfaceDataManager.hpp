/*
 { { *license|lines_prepend:" * " }}
 */
#pragma once

#include <QtWidgets>

class DataManager;

//FIXME I guess loading icons & pixmaps may need different approach
class InterfaceDataManager {

public:
	InterfaceDataManager(const DataManager *dataManager);
	~InterfaceDataManager();

	const QImage * getImage(const QString &name);
	const QPixmap * getPixmap(const QString &name);
	const QIcon * getIcon(const QString &name);

private:
	const DataManager *dataManager_;
	QHash<QString, QImage *> images_;
	QHash<QString, QPixmap *> pixmaps_;
	QHash<QString, QIcon *> icons_;


};
