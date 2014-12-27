/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Viewport;
class InterfaceDataManager;
class Mind;

static const QSize BottomPanelSize{300, 100};
static const QSize BottomPanelIconsSize{32, 32};

class GameWindow : public QWidget {
	Q_OBJECT;
public:
	GameWindow(InterfaceDataManager *dataManager, Mind *mind, QWidget *graphicsWidget, QWidget *parent = nullptr);

	Viewport *viewport();

private:
	void keyPressEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent *event);

	void initBottomPanel();
	void initViewport();

	InterfaceDataManager *dataManager_;
	Mind *mind_;

	Viewport *viewport_;
	QWidget *graphicsWidget_;
	QFrame *bottomPanel_;

signals:
	void showMainMenu();
};
