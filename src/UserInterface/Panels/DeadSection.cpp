/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Panels/DeadSection.hpp"

#include "UserInterface/Panels/UnitsPanel.hpp"
#include "UserInterface/Resources.hpp"

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
