/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Game/GameCommands.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Effect.hpp"
#include "Mind/Mind.hpp"
#include "Mind/ObjectEffectData.hpp"
#include "Mind/PointEffectData.hpp"
#include "UserInterface/BoardWidget.hpp"
#include "UserInterface/Game/GameViewport.hpp"
#include "UserInterface/Game/GameSelections.hpp"
#include "UserInterface/Resources.hpp"

GameCommands::GameCommands(Mind *m, BoardWidget *bw, const GameViewport &gv, const GameSelections &gs)
	: mind_(m),
	  boardWidget_(bw),
	  gameViewport_(gv),
	  gameSelections_(gs),
	  isVisiting_(false)
{}

void GameCommands::mousePressEvent(const QMouseEvent *event)
{
	QPointF place = gameViewport_.viewport()->getPhysicalCoordinates(event->pos());
	Object *target = gameViewport_.objectInPixelsPos(event->pos());

	if (event->button() == Qt::RightButton) {
		if (event->modifiers() & Qt::ControlModifier) {
			//SecondaryAction
			if (selectedUnits().size() == 1) {
				Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(*selectedUnits().begin()));
				auto command = chooseSecondaryCommand(unit, target);
				instructCommand(command, unit, place, target);
			}
		}
		else {
			// Primary Command
			for (auto &uid : selectedUnits()) {
				Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
				auto command = choosePrimaryCommand(unit, target);
				instructCommand(command, unit, place, target);
			}
		}
	}
}

void GameCommands::refresh()
{
	adjustCursor();
	checkForMoveCommand();
	checkForBaseVisit();
}

const QSet<int> &GameCommands::selectedUnits()
{
	return gameSelections_.selectedUnitsUids();
}

BS::Command GameCommands::choosePrimaryCommand(Unit *unit, Object *target)
{
	//if unit is camp
	if (unit->getState() == BS::State::IdleBase || unit->getState() == BS::State::RunBase) {
		if (target == nullptr)
			return BS::Command::Move;
		else
			return BS::Command::None;
	}

	// if this is ground or not iteresting target
	if (target == nullptr || target->getType() == BS::Type::Environment
	    || !mind_->getMapManager()->hasBeenSeen(target)) {
		if (unit->getState() == BS::State::Inside)
			return BS::Command::Leave;
		else
			return BS::Command::Move;
	}

	// only interesting targets remain
	switch (target->getType()) {
		case BS::Type::Unit:
			if (!mind_->getPlayerFaction()->isFriendly(target))
				return BS::Command::Attack;
			break;
		case BS::Type::Location:
			if (mind_->getPlayerFaction()->isFriendly(target)) {
				auto location = dynamic_cast<Location *>(target);
				if (unit->getState() != BS::State::Inside && !location->isFull())
					return BS::Command::Enter;
			}
			else
				return BS::Command::Attack;
			break;
		default:
			break;
	}

	return BS::Command::None;
}

BS::Command GameCommands::chooseSecondaryCommand(Unit *unit, Object *target)
{
	//if unit is camp
	if (unit->getState() == BS::State::IdleBase || unit->getState() == BS::State::RunBase) {
		if (target == nullptr)
			return BS::Command::Assemble;
		else
			return BS::Command::None;
	}

	// if this is ground or not iteresting target
	if (target == nullptr) {
		if (unit->getState() != BS::State::Inside)
			return BS::Command::Assemble;
		else
			return BS::Command::None;
	}

	// only interesting targets remain
	switch (target->getType()) {
		case BS::Type::Unit:
			if (mind_->getPlayerFaction()->isFriendly(target))
				return BS::Command::Heal;
			break;
		case BS::Type::Location:
			//TODO check if disassemblable - location, not fortification
			if (unit->getState() != BS::State::Inside)
				return BS::Command::Disassemble;
			break;
		default:
			break;
	}

		return BS::Command::None;
}

void GameCommands::instructCommand(BS::Command command, Unit *unit, QPointF point, Object *target)
{
	if (command != BS::Command::None)
		unit->setCommand(command);

	switch (command) {
		case BS::Command::Assemble:
			unit->setTargetPoint(point);
			return;
		case BS::Command::Attack:
			unit->setTargetObject(target->getUid());
			mind_->addEffect(Effect(Effects::HostileCommand, new ObjectEffectData(target),
			                 Effect::CommandEffectTimeout));
			return;
		case BS::Command::Disassemble:
			unit->setTargetObject(target->getUid());
			return;
		case BS::Command::Enter:
			unit->setTargetObject(target->getUid());
			mind_->addEffect(Effect(Effects::EnterCommand, new ObjectEffectData(target),
			                 Effect::CommandEffectTimeout));
			return;
		case BS::Command::Heal:
			unit->setTargetObject(target->getUid());
			mind_->addEffect(Effect(Effects::FriendlyCommand, new ObjectEffectData(target),
			                 Effect::CommandEffectTimeout));
			return;
		case BS::Command::Leave:
			return;
		case BS::Command::Move:
			unit->setTargetPoint(point);
			mind_->addEffect(Effect(Effects::MoveCommand, new PointEffectData(point), Effect::CommandEffectTimeout));
			return;
		default:
			return;
	}
}

void GameCommands::adjustCursor()
{
	// cursor not in boardWidget
	QPoint boardPos = boardWidget_->mapFromGlobal(boardWidget_->cursor().pos());
	if (!boardWidget_->geometry().contains(boardPos))
		return;

	auto target = gameViewport_.objectInPixelsPos(boardPos);
	BS::Command command = BS::Command::None;

	if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
		if (selectedUnits().size() == 1) {
			//check for possible secondary command
			Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(*selectedUnits().begin()));
			command = chooseSecondaryCommand(unit, target);
		}
	}
	else {
		if (!selectedUnits().isEmpty()) {
			//check for possible primary action
			Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(*selectedUnits().begin()));
			command = choosePrimaryCommand(unit, target);
		}
	}

	QCursor cursor = BSCursor(Cursors::PointerPrimary);

	switch (command) {
		case BS::Command::Assemble:
			cursor = BSCursor(Cursors::ArrowDownSecondary);
			break;
		case BS::Command::Attack:
			cursor = BSCursor(Cursors::Target);
			break;
		case BS::Command::Enter:
			cursor = BSCursor(Cursors::ArrowDownPrimary);
			break;
		case BS::Command::Heal:
			cursor = BSCursor(Cursors::HealCross);
			break;
		default:
			break;
	}

	boardWidget_->setCursor(cursor);
}

void GameCommands::checkForMoveCommand()
{
	if (!(QApplication::mouseButtons() & Qt::RightButton)
	    || QApplication::keyboardModifiers() & Qt::ControlModifier)
		return;

	QPoint pos = boardWidget_->mapFromGlobal(boardWidget_->cursor().pos());
	if (!boardWidget_->geometry().contains(pos))
		return;

	QPointF place = gameViewport_.viewport()->getPhysicalCoordinates(pos);
	Object *target = gameViewport_.objectInPixelsPos(pos);

	if (target != nullptr && target->getType() != BS::Type::Environment)
		return;

	for (auto &uid : selectedUnits()) {
		Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
		if (unit->getCommand() == BS::Command::Move) {
			unit->setCommand(BS::Command::Move);
			unit->setTargetPoint(place);
		}
	}
}

void GameCommands::checkForBaseVisit()
{
	auto camp = dynamic_cast<Location *>(mind_->getObjectFromUid(mind_->getPlayerFaction()->getCampUid()));
	if (!camp)
		return;

	if (camp->getUnitsUids().count() != 1) {
		isVisiting_ = false;
		return;
	}

	if (isVisiting_)
		return;

	auto unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(camp->getUnitsUids().at(0)));
	if (unit == nullptr) {
		err("What is in base, if not unit?");
		return;
	}

	emit visitBase(unit);
	isVisiting_ = true;

	unit->setCommand(BS::Command::Leave);
}
