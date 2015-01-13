/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Viewport;
class Mind;
class UnitsPanel;
class CampPanel;
class CampEquipmentWindow;
class JournalWindow;

static const int UpdateTimerInterval = 100; //in milliseconds

static const int ViewportMoveDelta = 10;
static const qreal ViewportZoomDelta = 0.05f;

class GameWindow : public QWidget {
	Q_OBJECT
public:
	GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent = nullptr);
	~GameWindow();

	Viewport *viewport();

public slots:
	void startUpdateLoop();

private:
	void keyPressEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent *event);

	void initCampEquipmentWidget();
	void initViewport();
	void initJournal();

	Mind *mind_;

	Viewport *viewport_;
	QWidget *graphicsWidget_;
	UnitsPanel *unitsPanel_;
	CampPanel *campPanel_;
	CampEquipmentWindow *campEquipmentWindow_;
	JournalWindow *journalWindow_;
	QTimer *updateTimer_;

private slots:
	void update();

signals:
	void showMainMenu();
};
