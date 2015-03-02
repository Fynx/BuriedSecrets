/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

QCursor BSCursor(const QString &cursor);

const QString DataPrefix = ":/";

namespace Icons {
	const QString Prefix = DataPrefix + "icons/";

	const QString Aggresive   = Prefix + "aggresive";
	const QString Camp        = Prefix + "camp";
	const QString Coward      = Prefix + "coward";
	const QString Food        = Prefix + "food";
	const QString Guard       = Prefix + "guard";
	const QString House       = Prefix + "house";
	const QString Journal     = Prefix + "journal";
	const QString Skull       = Prefix + "skull";
}

namespace Cursors {
	const QString Prefix           = DataPrefix + "cursors/";

	const QString ArrowDown        = Prefix + "arrow-down";
	const QString HealCross        = Prefix + "heal-cross";
	const QString PointerPrimary   = Prefix + "pointer-primary";
	const QString PointerSecondary = Prefix + "pointer-secondary";
	const QString Target           = Prefix + "target";
}
