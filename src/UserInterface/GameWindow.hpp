/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

#include "SelectionManager.hpp"

class BoardWidget;
class CampWindow;
class DataManager;
class FactionPanel;
class JournalWindow;
class Mind;
class UnitsPanel;
class UnitWindow;
class Viewport;

class GameWindow : public QWidget {
	Q_OBJECT
public:
	static const int UpdateTimerInterval; //in milliseconds

	GameWindow(Mind *mind, DataManager *dataManager, BoardWidget *boardWidget, QWidget *parent = nullptr);

	Viewport *viewport();

public slots:
	void startUpdateLoop();

private:
	void initWindows();
    void initBoardWidget();
	void initUnitsPanel();
	void initFactionPanel();

	void refresh();
	void pauseGame();
	void resumeGame();

	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);

	void tileLeft(QWidget *widget);
	void tileRight(QWidget *widget);
	void tileCenter(QWidget *widget);
	void adjustUnitsPanelGeometry();
	bool isSubwindowOpen();

	Mind *const mind_;
	DataManager *const dataManager_;

	BoardWidget *boardWidget_;
	UnitsPanel *unitsPanel_;
	FactionPanel *factionPanel_;
	CampWindow *campWindow_;
	JournalWindow *journalWindow_;
	UnitWindow *unitWindow_;

	QTimer *updateTimer_;

	SelectionManager selectionManager_;
	bool isPaused_;

private slots:
	void showCampWindow();
	void showJournalWindow();
	void showUnitWindow(int uid);
	void switchUnitWindow(int uid);
	void closeCampWindow();
	void closeJournalWindow();
	void closeUnitWindow();

signals:
	void showMainMenu();
};
