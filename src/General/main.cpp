#include <QtWidgets>
#include "General/General.hpp"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	General game;
	game.getMainWindow()->show();
	return app.exec();
}
