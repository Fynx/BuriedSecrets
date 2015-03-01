/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "DeadSection.hpp"

#include "UserInterface/UnitsPanel.hpp"
#include "UserInterface/ResourcesStrings.hpp"

DeadSection::DeadSection()
{
	setAutoFillBackground(true);

	setLayout(new QVBoxLayout);

	auto deadSign = new QLabel;
	deadSign->setPixmap(QPixmap(Icons::Skull));
	layout()->addWidget(deadSign);

}

QSize DeadSection::sizeHint() const
{
    return UnitsPanel::SectionSize;
}
