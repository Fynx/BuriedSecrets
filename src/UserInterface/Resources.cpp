/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Resources.hpp"

QCursor BSCursor(const QString &cursor)
{
	const QSize CursorSize{24, 24};
	static const QHash<QString, QCursor> BSCursors{
		{Cursors::ArrowDownPrimary,   QCursor(QPixmap(Cursors::ArrowDownPrimary).scaled(CursorSize),
		                                      CursorSize.width() / 2, CursorSize.height())},
		{Cursors::ArrowDownSecondary, QCursor(QPixmap(Cursors::ArrowDownSecondary).scaled(CursorSize),
		                                      CursorSize.width() / 2, CursorSize.height())},
		{Cursors::PointerPrimary,     QCursor(QPixmap(Cursors::PointerPrimary).scaled(CursorSize), 0, 0)},
		{Cursors::PointerSecondary,   QCursor(QPixmap(Cursors::PointerSecondary).scaled(CursorSize), 0, 0)},
		{Cursors::HealCross,          QCursor(QPixmap(Cursors::HealCross).scaled(CursorSize))},
		{Cursors::Target,             QCursor(QPixmap(Cursors::Target).scaled(CursorSize))}
	};

	return BSCursors.value(cursor, QCursor(Qt::ForbiddenCursor));
}
