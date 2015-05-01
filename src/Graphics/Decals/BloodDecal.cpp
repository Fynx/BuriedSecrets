/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/Decals/BloodDecal.hpp"

#include <QRectF>
#include <SFML/Graphics.hpp>

#include "Common/Geometry.hpp"
#include "Mind/EffectData.hpp"
#include "Mind/PointToPointEffectData.hpp"
#include "Graphics/GraphicalTextureSet.hpp"
#include "UserInterface/Viewport/Viewport.hpp"


BloodDecal::BloodDecal(const Viewport *viewport, const GraphicalTextureSet *decalTextureSet)
		: Decal{viewport, decalTextureSet}
{}


void BloodDecal::draw(sf::RenderTexture &renderTarget, const EffectData *effectData)
{
	const PointToPointEffectData *ptpData = dynamic_cast<const PointToPointEffectData *>(effectData);
	QPointF src = ptpData->getSource();
	QPointF dst = ptpData->getDestination();
	QPointF A = dst + dst - src;
	QPointF B = dst;
	QPointF C = B + QPointF{0, -1.0};
	float a = BS::Geometry::distance(A, B);
	float c = BS::Geometry::distance(A, C);
	float angle = acos((a * a - c * c) / 2.0f / a) * BS::Geometry::RADTOGEG;
	if (C.x() > A.x()) {
		angle = 360.0f - angle;
	} else if (BS::Geometry::isZero(C.x() - A.x())) {
		angle = A.y() - B.y() < 0.0f ? 0.0f : 180.0f;
	}

	sf::Sprite sprite;
	sprite.setTexture(*(decalTextureSet->getFrame()));
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y);
	sprite.setRotation(angle);

	QPointF pos = viewport->fromMetresToPixels(dst);
	sprite.setPosition(pos.x(), pos.y());
	QPointF scaleP = viewport->getWholeScale();
	scaleP /= qMax(scaleP.x(), scaleP.y());
	sprite.setScale(scaleP.x(), scaleP.y());

	sprite.setColor(sf::Color{255, 255, 255, 100});

	renderTarget.draw(sprite);
	renderTarget.display();
}


QRectF BloodDecal::getTargetRect (const EffectData *effectData)
{
	// TODO (not used yet)
	return QRectF{};
}


