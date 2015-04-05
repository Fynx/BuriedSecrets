/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Game/GameWindows.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"
#include "GameObjects/Unit.hpp"
#include "UserInterface/Windows/CampWindow.hpp"
#include "UserInterface/Windows/JournalWindow.hpp"
#include "UserInterface/Windows/UnitWindow.hpp"

GameWindows::GameWindows(Mind *m, DataManager *dm)
	: mind_(m),
	  dataManager_(dm)
{}

void GameWindows::adjustWindowsGeometry(const QRect &mainWindowGeometry, const QSize &unitsPanelSize)
{
	availableGeometry_ = mainWindowGeometry;
	availableGeometry_.setTop(unitsPanelSize.height());

	tileCenter(campWindow_);
	tileCenter(journalWindow_);
	tileCenter(unitWindow_);
}

void GameWindows::keyPressEvent(const QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_Escape:
			closeCampWindow();
			closeJournalWindow();
			closeUnitWindow();
			break;
		case Qt::Key_C:
			showCampWindow();
			break;
		case Qt::Key_J:
			showJournalWindow();
			break;
		case Qt::Key_I:
			for (auto uid : mind_->getPlayerFaction()->getAllUnitsUids())
				if (mind_->getPlayerFaction()->isAliveMember(uid)) {
					showUnitWindow(*(mind_->getPlayerFaction()->getUnitsUids().begin()));
					break;
				}
			break;
	}
}

void GameWindows::initWindows(QWidget *gameWindow)
{
	// CampWindow
	campWindow_ = new CampWindow(mind_, dataManager_);
	campWindow_->setParent(gameWindow);
	campWindow_->hide();
	connect(campWindow_, &CampWindow::exit, this, &GameWindows::closeCampWindow);

	// UnitWindow
	unitWindow_ = new UnitWindow(mind_, dataManager_);
	unitWindow_->setParent(gameWindow);
	unitWindow_->hide();
	connect(unitWindow_, &UnitWindow::exit, this, &GameWindows::closeUnitWindow);

	// JournalWindow
	journalWindow_ = new JournalWindow;
	journalWindow_->setParent(gameWindow);
	journalWindow_->hide();
	connect(journalWindow_, &JournalWindow::exit, this, &GameWindows::closeJournalWindow);
}

bool GameWindows::isSubwindowOpen() const
{
	return journalWindow_->isVisible() || campWindow_->isVisible() || unitWindow_->isVisible();
}

CampWindow *GameWindows::campWindow() const
{
	return campWindow_;
}

void GameWindows::showVisitWindow(Unit *unit)
{
	if (! isSubwindowOpen())
		emit pauseGame();

	tileLeft(campWindow_);
	tileRight(unitWindow_);

	journalWindow_->hide();
	campWindow_->refresh();
	unitWindow_->setUnit(unit);
	campWindow_->show();
	unitWindow_->show();
}

void GameWindows::showCampWindow()
{
	if (! isSubwindowOpen())
		emit pauseGame();

	campWindow_->refresh();
	campWindow_->show();
	journalWindow_->hide();
	unitWindow_->hide();
}

void GameWindows::showJournalWindow()
{
	if (! isSubwindowOpen())
		emit pauseGame();

	journalWindow_->show();
	campWindow_->hide();
	unitWindow_->hide();
}

void GameWindows::showUnitWindow(int uid)
{
	if (! isSubwindowOpen())
		emit pauseGame();


	Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (unit == nullptr) {
		err("Invalid unit UID to display");
		return;
	}
	unitWindow_->setUnit(unit);

	unitWindow_->show();
	campWindow_->hide();
	journalWindow_->hide();
}

void GameWindows::switchUnitWindow(int uid)
{
	Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (unit == nullptr) {
		err("Invalid unit UID to display");
		return;
	}

	if (unitWindow_->isVisible())
		unitWindow_->setUnit(unit);

}

void GameWindows::tileCenter(QWidget *widget)
{
	auto geom = availableGeometry_;
	geom.setWidth(availableGeometry_.width() / 2);
	geom.translate(geom.width() / 2, 0);

	widget->setGeometry(geom);
}

void GameWindows::tileLeft(QWidget *widget)
{
	auto geom = availableGeometry_;
	geom.setWidth(availableGeometry_.width() / 2);

	widget->setGeometry(geom);
}

void GameWindows::tileRight(QWidget *widget)
{
	auto geom = availableGeometry_;
	geom.setWidth(availableGeometry_.width() / 2);
	geom.translate(geom.width(), 0);

	widget->setGeometry(geom);
}

void GameWindows::closeCampWindow()
{
	campWindow_->hide();

	tileCenter(unitWindow_);
	tileCenter(campWindow_);

	if (! isSubwindowOpen())
		emit resumeGame();
}

void GameWindows::closeJournalWindow()
{
	journalWindow_->hide();
	emit resumeGame();
}

void GameWindows::closeUnitWindow()
{
	unitWindow_->hide();
	tileCenter(unitWindow_);
	tileCenter(campWindow_);

	if (! isSubwindowOpen())
		emit resumeGame();
}
