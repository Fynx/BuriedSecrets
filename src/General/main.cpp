/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include <QtWidgets>
#include "General/General.hpp"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	app.setApplicationName("BuriedSecrets");
	General game;
	game.getMainWindow()->show();
	return app.exec();
}
