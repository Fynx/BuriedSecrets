/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

/**
 * Section of units panel for displaying icons instead of info about units. (like "Dead" or "Psycho")
 */
class IconSection : public QWidget {

public:
	IconSection(const QString &icon);
	QSize sizeHint() const;
};
