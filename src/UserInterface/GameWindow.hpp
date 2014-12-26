/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Mind.hpp"
#include "UserInterface/Viewport.hpp"

#include <QtWidgets>

class DataManager;

static const QSize BottomPanelSize{300, 100};
// static const QMargins BottomPanelMargins{3, 3, 3, 3};

class GameWindow : public QWidget {
	Q_OBJECT;
public:
	GameWindow(DataManager *dataManager, Mind *mind, QWidget *graphicsWidget, QWidget *parent = nullptr);

	Viewport *viewport();

private:
	void keyPressEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent *event);

	void initBottomPanel();
	void initViewport();

	DataManager *dataManager_;
	Mind *mind_;

	Viewport *viewport_;
	QWidget *graphicsWidget_;
	QFrame *bottomPanel_;

signals:
	void switchToMainMenu();
};
