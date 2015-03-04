/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include <QtWidgets>
#include "ContentEditor/ContentEditor.hpp"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	ContentEditor editor;
	editor.show();
	return app.exec();
}
