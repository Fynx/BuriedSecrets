/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Item;

class ItemWidget : public QWidget {

public:
	ItemWidget(DataManager *dataManager);

	const Item *item() const;

	void setItem(const Item *item);

private:
	static const QSize PictureSize;

	void initLayout();
	QLayout *createMainPart();
	QLayout *createDetailsPart();
	void fillWidget();

	const Item *item_;
	DataManager *const dataManager_;

	QLabel *pictureLabel_;
	QLabel *nameLabel_;
	QLabel *weightLabel_;
};
