#pragma once

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
	UserInterface(MapManager *mapManager);
	~UserInterface();

	QMainWindow * getMainWindow();

private:
	MapManager  *mapManager;
	QMainWindow *mainWindow;
};