/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Panels/IconSection.hpp"

#include "UserInterface/Panels/UnitsPanel.hpp"

IconSection::IconSection(const QString &icon)
{
	setAutoFillBackground(true);

	setLayout(new QVBoxLayout);

	auto label = new QLabel;
	label->setPixmap(QPixmap(icon));
	layout()->addWidget(label);
}

QSize IconSection::sizeHint() const
{
    return UnitsPanel::SectionSize;
}
