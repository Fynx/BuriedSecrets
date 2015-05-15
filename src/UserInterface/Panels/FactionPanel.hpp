/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Mind;

static const QSize FactionPanelSize{260, 60};
static const QSize IconsSize{32, 32};

/**
 * Widget to show information and options of player's faction.
 */
class FactionPanel : public QFrame {
	Q_OBJECT
public:
	FactionPanel(const Mind *m);
	void refresh();

private:
	void initLayout();
	QLayout *createFoodLayout();

	const Mind *const mind_;

	QLabel *foodAmount_;

	QPushButton *campBtn_;
	QPushButton *journalBtn_;
	QPushButton *exitBtn_;

signals:
	void journalActivated();
	void campActivated();
	void exitActivated();
};
