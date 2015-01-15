/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class CampEquipmentWindow;
class CampPanel;
class JournalWindow;
class Mind;
class Object;
class UnitsPanel;
class Viewport;

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
	void mousePressEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);

	void handleGameWidgetClicked(const QPoint &pos, Qt::MouseButton button);
	void initViewport();

	const QList<Object *> &fiterSelection(const QList<Object *> &objects);
	void selectObjects(const QList<Object *> &objects);

	Mind *mind_;

	Viewport *viewport_;
	QWidget *graphicsWidget_;
	UnitsPanel *unitsPanel_;
	CampPanel *campPanel_;
	CampEquipmentWindow *campEquipmentWindow_;
	JournalWindow *journalWindow_;
	QTimer *updateTimer_;

	QList<Object *> selectedObjects_;

private slots:
	void refresh();
	void adjustUnitsPanelGeometry();
	void selectUnit(int uid);

signals:
	void showMainMenu();
};
