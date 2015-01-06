/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Viewport;
class Mind;
class UnitsPanel;
class CampEquipmentWindow;
class JournalWindow;

//TODO orginize this
static const QSize BottomPanelSize{300, 100};
static const QSize BottomPanelIconsSize{32, 32};

static const int ViewportMoveDelta = 10;
static const qreal ViewportZoomDelta = 0.05f;

class GameWindow : public QWidget {
	Q_OBJECT
public:
	GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent = nullptr);
	~GameWindow();

	Viewport *viewport();

private:
	void keyPressEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent *event);

	void initBottomPanel();
	void initCampEquipmentWidget();
	void initViewport();
	void initJournal();

	Mind *mind_;

	Viewport *viewport_;
	QWidget *graphicsWidget_;
	UnitsPanel *unitsPanel_;
	QFrame *bottomPanel_;
	CampEquipmentWindow *campEquipmentWindow_;
	JournalWindow *journalWindow_;

signals:
	void showMainMenu();
};
