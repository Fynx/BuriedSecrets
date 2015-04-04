/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "Common/Enums.hpp"

class PostGameMenu : public QWidget {
	Q_OBJECT

public:
    PostGameMenu();

	void setEnding(BS::GameState gs);

private:
	static const QMargins ContentsMargins;

	void initLayout();

	QLabel *textLabel_;
	QPushButton *mainMenuBtn_;

signals:
	void goToMainMenu();
};
