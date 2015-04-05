/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Mind;

static const QSize FactionPanelSize{300, 100};
static const QSize IconsSize{64, 64};

class FactionPanel : public QFrame {
	Q_OBJECT
public:
	FactionPanel();
	void refresh(const Mind *mind);

private:
	void initLayout();
	QLayout *createFoodLayout();

	QPushButton *campBtn_;
	QPushButton *journalBtn_;

	QLabel *foodAmount_;

signals:
	void journalActivated();
	void campActivated();
};
