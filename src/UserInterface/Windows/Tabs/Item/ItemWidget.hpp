/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Item;
class Prototype;

class ItemWidget : public QWidget {

public:
	ItemWidget(DataManager *dataManager);

	const Prototype *prototype() const;

	void setItem(const Item *item);
	void setPrototype(const Prototype *prototype);

	void clear();

private:
	static const int EmptyIndex = 0;
	static const int FilledIndex = 1;

	static const QSize PictureSize;
	static const QSize StarSize;
	static const QMargins DetailsContentMargins;
	static const QFont DetailsFont;
	static const QFont TitlesFont;
	static const int VerticalSpacing = 5;
	static const int HorizontalSpacing = 15;

	void initLayout();
	QLayout *createMainPart();
	QLayout *createDetailsPart();
	void fillWidget();
	void fillQuality(int q);
	void fillSpecifics();
	void addSpecific(const QString &key, const QString &value);
	void addSpecificProperty(const QString &key, const QString &property);

	const Prototype *prototype_;
	DataManager *const dataManager_;

	QStackedLayout *layout_;

	QLabel *pictureLabel_;
	QLabel *nameLabel_;

	QLabel *descriptionLabel_;
	QLabel *itemTypeLabel_;
	QList<QLabel *> stars_;
	QLabel *weightLabel_;

	QFormLayout *specificsLayout_;
};
