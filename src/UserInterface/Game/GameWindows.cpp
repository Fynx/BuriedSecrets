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
	  dataManager_(dm),
	  openedWindow_(Window::Game)
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
			if (openedWindow_ != Window::UnitDecision)
				showWindow(Window::Game);
			break;
		case Qt::Key_C:
			showWindow(Window::Camp);
			break;
		case Qt::Key_J:
			showWindow(Window::Journal);
			break;
		case Qt::Key_I:
			showUnitWindow(anyAliveUnitUid());
			break;
		case Qt::Key_L:
			showLoadout();
			break;
	}
}

void GameWindows::initWindows(QWidget *gameWindow)
{
	// CampWindow
	campWindow_ = new CampWindow(mind_, dataManager_);
	campWindow_->setParent(gameWindow);
	campWindow_->hide();
	connect(campWindow_, &CampWindow::exit, this, &GameWindows::closeSubwindow);

	// UnitWindow
	unitWindow_ = new UnitWindow(mind_, dataManager_);
	unitWindow_->setParent(gameWindow);
	unitWindow_->hide();
	connect(unitWindow_, &UnitWindow::exit, this, &GameWindows::closeSubwindow);

	// JournalWindow
	journalWindow_ = new JournalWindow(mind_, dataManager_);
	journalWindow_->setParent(gameWindow);
	journalWindow_->hide();
	connect(journalWindow_, &JournalWindow::exit, this, &GameWindows::closeSubwindow);
}

bool GameWindows::isSubwindowOpen() const
{
	return openedWindow_ != Window::Game;
}

void GameWindows::refresh()
{
	auto pendingUnits = mind_->getPlayerFaction()->getPendingUnitsUids();
	if (pendingUnits.isEmpty() || openedWindow_ == Window::UnitDecision)
		return;

	showUnitDecision(pendingUnits.first());
}

void GameWindows::showVisitWindow(Unit *unit)
{
	unitWindow_->setUnit(unit);
	showWindow(Window::Visit);
}

void GameWindows::showUnitDecision(int uid)
{
	unitWindow_->setUnitForDecision(uid);
	QMessageBox msgBox;
	msgBox.setWindowTitle(tr("New unit"));
	msgBox.setText(tr("An outsider wants to join your faction."));
	msgBox.exec();
	showWindow(Window::UnitDecision);
}

void GameWindows::showCampWindow()
{
	showWindow(Window::Camp);
}

void GameWindows::showJournalWindow()
{
	showWindow(Window::Journal);
}

void GameWindows::showLoadout()
{
	auto uid = anyAliveUnitUid();
	Unit *unit = mind_->getUnit(uid);
	if (unit == nullptr) {
		err("Invalid unit UID to display");
		return;
	}
	unitWindow_->setUnit(unit);
	showWindow(Window::Loadout);
}

void GameWindows::showUnitWindow(int uid)
{
	Unit *unit = mind_->getUnit(uid);
	if (unit == nullptr) {
		err("Invalid unit UID to display");
		return;
	}
	unitWindow_->setUnit(unit);
	showWindow(Window::Unit);
}

void GameWindows::switchUnitWindow(int uid)
{

	Unit *unit = mind_->getUnit(uid);
	if (unit == nullptr) {
		err("Invalid unit UID to display");
		return;
	}

	if (openedWindow_ == Window::Visit)
		showWindow(Window::Unit);

	if (unitWindow_->isVisible())
		unitWindow_->setUnit(unit);
}

void GameWindows::showJournalEntry(int uid)
{
	journalWindow_->setCurrentEntry(uid);
	showWindow(Window::Journal);
}

void GameWindows::showWindow(GameWindows::Window window)
{
	if (openedWindow_ == window)
		return;

	//window will change & it's no longer game, so we have to pause game
	if (openedWindow_ == Window::Game)
		emit pauseGame();

	campWindow_->hide();
	journalWindow_->hide();
	unitWindow_->hide();

	switch (window) {
		case Window::Camp:
			tileCenter(campWindow_);
			campWindow_->refresh();
			campWindow_->show();
			break;
		case Window::Game:
			break;
		case Window::Journal:
			journalWindow_->refresh();
			journalWindow_->show();
			break;
		case Window::Unit:
		case Window::UnitDecision:
			tileCenter(unitWindow_);
			unitWindow_->show();
			break;
		case Window::Loadout:
			campWindow_->setCurrentTab(CampWindow::BriefingIndex);
		case Window::Visit:
			if (window == Window::Visit) //due to fall through
				campWindow_->setCurrentTab(CampWindow::EquipmentIndex);
			tileLeft(campWindow_);
			tileRight(unitWindow_);
			campWindow_->refresh();
			campWindow_->show();
			unitWindow_->show();
			break;
	}

	openedWindow_ = window;

	if (openedWindow_ == Window::Game)
		emit resumeGame();
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

void GameWindows::closeSubwindow()
{
	showWindow(Window::Game);
}

int GameWindows::anyAliveUnitUid()
{
	for (auto uid : mind_->getPlayerFaction()->getAllUnitsUids())
		if (mind_->getPlayerFaction()->isAliveMember(uid))
			return uid;
	return Object::InvalidUid;
}
