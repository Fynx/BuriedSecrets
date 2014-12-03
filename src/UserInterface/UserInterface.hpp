/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Graphics/GraphicsWidget.hpp"
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
	UserInterface(MapManager *mapManager, Mind *mind, QWidget *graphicsWidget);
	~UserInterface();

	QMainWindow *getMainWindow();

private:
	MapManager  *mapManager;
	Mind        *mind;

	QMainWindow *mainWindow;
	QWidget     *graphicsWidget;
};