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
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);

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
	void refresh();
	void adjustUnitsPanelGeometry();

signals:
	void showMainMenu();
};
