/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

/**
 * Custom QListWidget for items to implement drag'n'drop correctly.
 */
class ItemsListWidget : public QListWidget {
	Q_OBJECT

public:
    ItemsListWidget(QWidget *parent = nullptr);

	void disableDragAndDrop();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

private:
	void performDrag();

	bool dragAndDropEnabled_;
	QPoint dragStartPos_;

signals:
	void itemMovedIn(int uid);
	void itemMovedOut(int uid);
};
