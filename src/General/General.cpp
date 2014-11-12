#include "General/General.h"

#include <QtWidgets>

General::General()
{
	QLabel *l = new QLabel(this);
	l->setText("BuriedSecrets here. Hello world.");
	setCentralWidget(l);
	QAction *a = new QAction(this);
	a->setText("Quit");
	connect(a, SIGNAL(triggered()), SLOT(close()));
	menuBar()->addMenu("File")->addAction(a);
}
