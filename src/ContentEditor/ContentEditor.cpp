/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "ContentEditor/ContentEditor.hpp"

ContentEditor::ContentEditor()
{
	initObjects();
	initLayout();
	showFullScreen();
}

ContentEditor::~ContentEditor()
{}

void ContentEditor::initObjects()
{
	tabWidget = new QTabWidget();

	prototypesEditor = new PrototypesEditor(this);

	tabWidget->addTab(prototypesEditor, "Prototypes");

	buttonSave = new QPushButton("Save");
	connect(buttonSave, &QPushButton::clicked, this, &ContentEditor::onSave);

	buttonQuit = new QPushButton("Quit");
	connect(buttonQuit, &QPushButton::clicked, this, &ContentEditor::onQuit);
}

void ContentEditor::initLayout()
{
	QHBoxLayout *layoutButtons = new QHBoxLayout();
	layoutButtons->setAlignment(Qt::AlignRight);

	buttonSave->setFixedSize({100, 50});
	layoutButtons->addWidget(buttonSave);

	QSpacerItem *spacerButtons = new QSpacerItem(50, 50);
	layoutButtons->addItem(spacerButtons);

	buttonQuit->setFixedSize({100, 50});
	layoutButtons->addWidget(buttonQuit);


	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(tabWidget);
	layout->addItem(layoutButtons);

	setLayout(layout);
}

void ContentEditor::onSave()
{
	qDebug() << "Save";
	//TODO
}

/** Save on quit, too */
void ContentEditor::onQuit()
{
	qDebug() << "Quit";
	onSave();
	close();
}

void ContentEditor::keyPressEvent(QKeyEvent *event)
{
	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Q)
		onQuit();
	QWidget::keyPressEvent(event);
}
