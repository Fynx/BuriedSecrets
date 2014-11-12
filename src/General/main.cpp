#include <QtWidgets>
#include "General/General.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	General game;
	game.show();
	return app.exec();
}
