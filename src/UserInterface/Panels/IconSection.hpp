/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class IconSection : public QWidget {

public:
	IconSection(const QString &icon);
	QSize sizeHint() const;
};
