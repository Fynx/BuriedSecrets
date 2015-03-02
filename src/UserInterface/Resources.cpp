/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Resources.hpp"
#include <X11/Xcursor/Xcursor.h>

QCursor BSCursor(const QString &cursor)
{
	const QSize CursorSize{24, 24};
	static const QHash<QString, QCursor> BSCursors{
		{Cursors::PointerPrimary,   QCursor(QPixmap(Cursors::PointerPrimary).scaled(CursorSize), 0, 0)},
		{Cursors::PointerSecondary, QCursor(QPixmap(Cursors::PointerSecondary).scaled(CursorSize), 0, 0)},
		{Cursors::ArrowDown,        QCursor(QPixmap(Cursors::ArrowDown).scaled(CursorSize),
		                                    CursorSize.width() / 2, CursorSize.height())},
		{Cursors::HealCross,        QCursor(QPixmap(Cursors::HealCross).scaled(CursorSize))},
		{Cursors::Target,           QCursor(QPixmap(Cursors::Target).scaled(CursorSize))}
	};

	return BSCursors.value(cursor, QCursor(Qt::ForbiddenCursor));
}
