/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GraphicsWidget.hpp"

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif


GraphicsWidget::GraphicsWidget()
	: BoardWidget{}, initialized{false}
{
	// Setup some states to allow direct rendering into the widget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);

	// Set strong focus to enable keyboard events to be received
	setFocusPolicy(Qt::StrongFocus);
}


void GraphicsWidget::showEvent(QShowEvent *)
{
	if (!initialized) {
		// Under X11, we need to flush the commands sent to the server to ensure that
		// SFML will get an updated view of the windows.
		#ifdef Q_WS_X11
		XFlush(QX11Info::display());
		#endif

		// Create the SFML window with the widget handle
		sf::Window::create(winId());

		initialized = true;
	}
}

QPaintEngine * GraphicsWidget::paintEngine() const
{
	return nullptr;
}

void GraphicsWidget::paintEvent(QPaintEvent*)
{
	// Display on screen
	display();
}
