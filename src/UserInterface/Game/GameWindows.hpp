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

class GameWindows : public QObject {
	Q_OBJECT
public:
	GameWindows(Mind *m, DataManager *dm);

	void initWindows(QWidget *mainWidget);
	void adjustWindowsGeometry(const QRect &mainWindowGeometry, const QSize &unitsPanelSize);

	void keyPressEvent(const QKeyEvent *event);

	bool isSubwindowOpen() const;
	CampWindow *campWindow() const;

public slots:
	void showVisitWindow(Unit *unit);
	void showCampWindow();
	void showJournalWindow();
	void showUnitWindow(int uid);
	void switchUnitWindow(int uid);

private:
	void tileLeft(QWidget *widget);
	void tileRight(QWidget *widget);
	void tileCenter(QWidget *widget);

	Mind *const mind_;
	DataManager *const dataManager_;

	CampWindow *campWindow_;
	JournalWindow *journalWindow_;
	UnitWindow *unitWindow_;

	QRect availableGeometry_;

private slots:
	void closeCampWindow();
	void closeJournalWindow();
	void closeUnitWindow();

signals:
	void pauseGame();
	void resumeGame();
};
