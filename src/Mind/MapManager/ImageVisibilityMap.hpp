/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QImage>
#include <QPainter>

#include "Mind/MapManager/VisibilityMap.hpp"


/**
 * @brief An image-based VisibilityMap implementation.
 *
 * The underlying structure is a QImage. All the updates are drawn into it. It is basically a matrix-based
 * implementation, but an image is a lot more convenient to use.
 */
class ImageVisibilityMap : public VisibilityMap {
public:
	ImageVisibilityMap(const QSize &size);

	void update(const VisibilityUpdate &visibilityUpdate) override;
	bool isVisible(const QPointF &point) const override;
	void clear() override;

protected:
	bool isVisible(const Unit *from, const QPointF &target, const Object *owner,
		const PhysicsEngine *physicsEngine) const override;

private:
	QImage mapImage;
	QImage tempImage;
};
