/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "Common/Enums.hpp"

class PostGameWindow : public QWidget {
	Q_OBJECT

public:
    PostGameWindow();

	void setEnding(BS::GameState gs);

private:
	static const QMargins ContentsMargins;

	void initLayout();

	QLabel *textLabel_;
	QPushButton *mainMenuBtn_;

signals:
	void goToMainMenu();
};
