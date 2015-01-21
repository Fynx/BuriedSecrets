/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "GameWidgetManager.hpp"

class CampEquipmentWindow;
class CampPanel;
class JournalWindow;
class Mind;
class UnitsPanel;
class UnitWindow;
class Viewport;

class GameWindow : public QWidget {
	Q_OBJECT
public:
	static const int UpdateTimerInterval; //in milliseconds

	GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent = nullptr);

	Viewport *viewport();

public slots:
	void startUpdateLoop();

private:
	void initUnitsPanel();
	void initWindows();
	void refresh();

	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);

	void tileLeft(QWidget *widget);
	void tileRight(QWidget *widget);
	void tileCenter(QWidget *widget);
	void adjustUnitsPanelGeometry();

	Mind *mind_;
	GameWidgetManager gameWidgetManager_;

	QWidget *gameWidget_;
	UnitsPanel *unitsPanel_;
	CampPanel *campPanel_;
	CampEquipmentWindow *campEquipmentWindow_;
	JournalWindow *journalWindow_;
	UnitWindow *unitWindow_;

	QTimer *updateTimer_;

private slots:
	void showCampMenu();
	void showJournal();
	void showUnitMenu(int uid);
	void closeCampMenu();
	void closeJournal();
	void closeUnitMenu();

signals:
	void showMainMenu();
};
