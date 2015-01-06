/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class JournalWindow : public QFrame {
public:
	JournalWindow();

private:
	void initLayout();

	QPushButton *closeBtn_;
};
