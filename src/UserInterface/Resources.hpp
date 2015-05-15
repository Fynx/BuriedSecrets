/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

/**
 * Place to store resources paths listed in qrc file.
 */

QCursor BSCursor(const QString &cursor);

const QString DataPrefix = ":/";

namespace Icons {
	const QString Prefix = DataPrefix + "icons/";

	const QString Aggresive        = Prefix + "aggresive";
	const QString Camp             = Prefix + "camp";
	const QString CampSelected     = Prefix + "camp-selected";
	const QString Empty            = Prefix + "empty";
	const QString Exit             = Prefix + "exit";
	const QString Food             = Prefix + "food";
	const QString Guard            = Prefix + "guard";
	const QString Location         = Prefix + "house";
	const QString LocationSelected = Prefix + "house-selected";
	const QString Journal          = Prefix + "journal";
	const QString Psycho           = Prefix + "psycho";
	const QString Skull            = Prefix + "skull";
}

namespace Cursors {
	const QString Prefix           = DataPrefix + "cursors/";

	const QString ArrowDownPrimary   = Prefix + "arrow-down-primary";
	const QString ArrowDownSecondary = Prefix + "arrow-down-secondary";
	const QString HealCross          = Prefix + "heal-cross";
	const QString PointerPrimary     = Prefix + "pointer-primary";
	const QString PointerSecondary   = Prefix + "pointer-secondary";
	const QString Target             = Prefix + "target";
}
