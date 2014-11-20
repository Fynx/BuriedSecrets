#pragma once

#include "Mind/Mind.hpp"

#include <QtWidgets>

// Nah, not a QObject, just for now
class MapManager : public QObject {
Q_OBJECT;
public:
	virtual void loadMap() = 0;
	virtual void saveMap() = 0;

	//...
};

class UserInterface : public QObject {

Q_OBJECT;
public:
	UserInterface(MapManager *mapManager, Mind *mind, QWidget *mapView);
	~UserInterface();

	QMainWindow *getMainWindow();

private:
	MapManager  *mapManager;
	Mind        *mind;

	QMainWindow *mainWindow;
	QWidget     *mapView;
};