/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Menus/LoadGameMenu.hpp"

#include <QFileInfo>
#include "DataManager/DataManager.hpp"

const QMargins LoadGameMenu::ContentsMargins{300, 32, 300, 32};

LoadGameMenu::LoadGameMenu(QWidget *parent)
	: QWidget(parent)
{
	setContentsMargins(ContentsMargins);

	initLayout();
}

void LoadGameMenu::initLayout()
{
	auto mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	auto title = new QLabel(tr("Load Game"));
	title->setFont(QFont("Times", 36));
	title->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(title, 2);

	mainLayout->addWidget(createSavesList(), 3);
	mainLayout->addStretch(1);
	mainLayout->addWidget(createCloseBtn());
}

QWidget *LoadGameMenu::createSavesList()
{
	savesList_ = new QListWidget();
	refreshList();
	connect(savesList_, &QListView::doubleClicked, this, &LoadGameMenu::onSaveDoubleClicked);

	return savesList_;
}

QWidget *LoadGameMenu::createCloseBtn()
{
	QFont buttonFont("Times", 24);
	QSizePolicy btnSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	auto closeBtn = new QPushButton(tr("Close"));
	closeBtn->setFont(buttonFont);
	closeBtn->setSizePolicy(btnSizePolicy);
	connect(closeBtn, &QPushButton::clicked, this, &LoadGameMenu::closeActivated);
	return closeBtn;
}


void LoadGameMenu::refreshList()
{
	savesList_->clear();

	QDir savesDir(DataManager::savesPath(), QString("*") + DataManager::SavesExtension,
				  QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::Readable);

	QStringList saves;
	for (auto save : savesDir.entryList()) {
		QFileInfo saveInfo(save);
		saves.append(saveInfo.baseName());
	}

		for (auto &save : saves) {
			auto lwi = new QListWidgetItem(save, savesList_);
			lwi->setFlags(Qt::ItemFlag::ItemIsSelectable | Qt::ItemIsEnabled);
			lwi->setData(Qt::UserRole, QVariant(save));
			lwi->setFont(QFont("Times", 18));
		}
}

void LoadGameMenu::onSaveDoubleClicked(const QModelIndex &index)
{
	auto path = DataManager::savesPath() + index.data().toString() + DataManager::SavesExtension;
	emit loadGame(path);
}
