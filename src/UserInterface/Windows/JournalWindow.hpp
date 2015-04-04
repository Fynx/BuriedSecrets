/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class JournalWindow : public QFrame {
	Q_OBJECT
public:
	JournalWindow();

private:
	void initLayout();

	QPushButton *closeBtn_;

signals:
	void exit();
};
