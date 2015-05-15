/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class CampWindow;
class DataManager;
class JournalWindow;
class Mind;
class Unit;
class UnitWindow;

/**
 * Manages all in-game popup windows.
 * Checks for units wanting to join.
 */
class GameWindows : public QObject {
	Q_OBJECT
public:
	GameWindows(Mind *m, DataManager *dm);

	void initWindows(QWidget *mainWidget);
	void adjustWindowsGeometry(const QRect &mainWindowGeometry, const QSize &unitsPanelSize);

	void keyPressEvent(const QKeyEvent *event);
	bool isSubwindowOpen() const;
	void refresh();

public slots:
	void showVisitWindow(Unit *unit);
	void showCampWindow();
	void showJournalWindow();
	void showLoadout();
	void showUnitWindow(int uid);
	void switchUnitWindow(int uid);
	void showJournalEntry(int uid);

private:
	enum class Window {
		Camp,
		UnitDecision,
		Game,
		Journal,
		Unit,
		Visit,
		Loadout,
	};

	void showUnitDecision(int uid);
	void showWindow(Window window);
	void tileLeft(QWidget *widget);
	void tileRight(QWidget *widget);
	void tileCenter(QWidget *widget);
	int anyAliveUnitUid();

	Mind *const mind_;
	DataManager *const dataManager_;
	Window openedWindow_;

	CampWindow *campWindow_;
	JournalWindow *journalWindow_;
	UnitWindow *unitWindow_;

	QRect availableGeometry_;

private slots:
	void closeSubwindow();

signals:
	void pauseGame();
	void resumeGame();
};
