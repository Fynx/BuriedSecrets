/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Menus/SaveGameMenu.hpp"

#include "DataManager/DataManager.hpp"

const QMargins SaveGameMenu::ContentsMargins{300, 32, 300, 32};

SaveGameMenu::SaveGameMenu(QWidget *parent)
	: QWidget(parent)
{
	setContentsMargins(ContentsMargins);

	initLayout();
}

void SaveGameMenu::initLayout()
{
	auto mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	auto title = new QLabel(tr("Save Game"));
	title->setFont(QFont("Times", 36));
	title->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(title, 2);

	mainLayout->addWidget(createSavesList(), 3);
	mainLayout->addWidget(createNewBtn());
	mainLayout->addStretch(1);
	mainLayout->addWidget(createCloseBtn());
}

QWidget *SaveGameMenu::createSavesList()
{
	savesList_ = new QListWidget();
	refreshList();
	connect(savesList_, &QListView::doubleClicked, this, &SaveGameMenu::onSaveDoubleClicked);

	return savesList_;
}

QWidget *SaveGameMenu::createNewBtn()
{
	QFont buttonFont("Times", 24);
	QSizePolicy btnSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	auto newBtn = new QPushButton(tr("New"));
	newBtn->setFont(buttonFont);
	newBtn->setSizePolicy(btnSizePolicy);
	connect(newBtn, &QPushButton::clicked, this, &SaveGameMenu::onNewClicked);
	return newBtn;
}

QWidget *SaveGameMenu::createCloseBtn()
{
	QFont buttonFont("Times", 24);
	QSizePolicy btnSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	auto closeBtn = new QPushButton(tr("Close"));
	closeBtn->setFont(buttonFont);
	closeBtn->setSizePolicy(btnSizePolicy);
	connect(closeBtn, &QPushButton::clicked, this, &SaveGameMenu::closeActivated);
	return closeBtn;
}

void SaveGameMenu::refreshList()
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

void SaveGameMenu::onSaveDoubleClicked(const QModelIndex &index)
{
	askForName(index.data().toString());
}

void SaveGameMenu::onNewClicked()
{
	askForName();
}

void SaveGameMenu::askForName(const QString &name)
{
	QString filename;
	auto title = tr("Save");
	auto prompt = tr("Enter file name.\nIt must not be empty or contains anything else than\nletters, numbers, spaces, \"-\" or \"_\".");
	bool ok = false;
	filename = QInputDialog::getText(nullptr, title,
                                     prompt, QLineEdit::Normal, name, &ok);

	while (ok && not isFilenameValid(filename))
		filename = QInputDialog::getText(nullptr, title,
		                                 prompt, QLineEdit::Normal, name, &ok);

	emit saveGame(DataManager::savesPath() + filename + DataManager::SavesExtension);
	refreshList();
}

bool SaveGameMenu::isFilenameValid(const QString &filename)
{
	if (filename.isEmpty())
		return false;

	for (QChar c : filename) {
		if (c.isLetterOrNumber() || c == ' ' || c == '_' || c == '-')
			continue;
		return false;
	}
	return true;
}
