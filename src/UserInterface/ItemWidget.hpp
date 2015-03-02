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
	static const QSize StarSize;
	static const QMargins DetailsContentMargin;
	static const QFont DetailsFont;
	static const QFont TitlesFont;
	static const int VerticalSpacing = 10;
	static const int HorizontalSpacing = 15;

	void initLayout();
	QLayout *createMainPart();
	QLayout *createDetailsPart();
	void fillWidget();
	void fillQuality(int q);

	const Item *item_;
	DataManager *const dataManager_;

	QLabel *pictureLabel_;
	QLabel *nameLabel_;

	QLabel *descriptionLabel_;
	QLabel *itemTypeLabel_;
	QList<QLabel *> stars_;
	QLabel *weightLabel_;
	QLabel *componentsLabel_;
	QLabel *componentsTitle_;
};
