/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include <QtWidgets>
#include "General/General.hpp"

int main(int argc, char** argv)
{
// 	QCoreApplication::addLibraryPath("./libs/plugins/");
	QApplication app(argc, argv);
	General game;
	game.getMainWindow()->show();
	return app.exec();
}
