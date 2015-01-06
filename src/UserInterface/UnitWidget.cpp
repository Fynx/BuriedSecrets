/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitWidget.hpp"

UnitWidget::UnitWidget()
{
	setAutoFillBackground(true);
	setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	initWidgets();
	initLayout();
}

QSize UnitWidget::sizeHint() const
{
	return WidgetSize;
}

void UnitWidget::initWidgets()
{
	face_ = new QPushButton("Face");
	face_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	name_ = new QLabel("Bogdan");
	name_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void UnitWidget::initLayout()
{
	setLayout(new QHBoxLayout);
	layout()->addWidget(face_);
	layout()->addWidget(name_);
}
