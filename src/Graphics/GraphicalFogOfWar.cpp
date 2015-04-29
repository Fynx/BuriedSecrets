/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Graphics/GraphicalFogOfWar.hpp"

#include "Mind/MapManager/MapManager.hpp"
#include "UserInterface/Viewport/Viewport.hpp"


const char *blurH = "\
uniform sampler2D screenColorBuffer;\
const float blurSize = 0.1/256.0;\
\
void main(void)\
{\
   vec2 vTexCoord = gl_TexCoord[0].st;\
   vec4 sum = vec4(0.0);\
   sum += texture2D(screenColorBuffer, vec2(vTexCoord.x - 4.0*blurSize, vTexCoord.y)) * 0.05;\
   sum += texture2D(screenColorBuffer, vec2(vTexCoord.x - 3.0*blurSize, vTexCoord.y)) * 0.09;\
   sum += texture2D(screenColorBuffer, vec2(vTexCoord.x - 2.0*blurSize, vTexCoord.y)) * 0.12;\
   sum += texture2D(screenColorBuffer, vec2(vTexCoord.x - blurSize, vTexCoord.y)) * 0.15;\
   sum += texture2D(screenColorBuffer, vec2(vTexCoord.x, vTexCoord.y)) * 0.16;\
   sum += texture2D(screenColorBuffer, vec2(vTexCoord.x + blurSize, vTexCoord.y)) * 0.15;\
   sum += texture2D(screenColorBuffer, vec2(vTexCoord.x + 2.0*blurSize, vTexCoord.y)) * 0.12;\
   sum += texture2D(screenColorBuffer, vec2(vTexCoord.x + 3.0*blurSize, vTexCoord.y)) * 0.09;\
   sum += texture2D(screenColorBuffer, vec2(vTexCoord.x + 4.0*blurSize, vTexCoord.y)) * 0.05;\
   gl_FragColor = sum;\
}";


const char *blurV = "\
uniform sampler2D screenTexture;\
const float blurSize = 0.1/256.0;\
 \
void main(void)\
{\
   vec2 vTexCoord = gl_TexCoord[0].st;\
   vec4 sum = vec4(0.0);\
   sum += texture2D(screenTexture, vec2(vTexCoord.x, vTexCoord.y - 4.0*blurSize)) * 0.05;\
   sum += texture2D(screenTexture, vec2(vTexCoord.x, vTexCoord.y - 3.0*blurSize)) * 0.09;\
   sum += texture2D(screenTexture, vec2(vTexCoord.x, vTexCoord.y - 2.0*blurSize)) * 0.12;\
   sum += texture2D(screenTexture, vec2(vTexCoord.x, vTexCoord.y - blurSize)) * 0.15;\
   sum += texture2D(screenTexture, vec2(vTexCoord.x, vTexCoord.y)) * 0.16;\
   sum += texture2D(screenTexture, vec2(vTexCoord.x, vTexCoord.y + blurSize)) * 0.15;\
   sum += texture2D(screenTexture, vec2(vTexCoord.x, vTexCoord.y + 2.0*blurSize)) * 0.12;\
   sum += texture2D(screenTexture, vec2(vTexCoord.x, vTexCoord.y + 3.0*blurSize)) * 0.09;\
   sum += texture2D(screenTexture, vec2(vTexCoord.x, vTexCoord.y + 4.0*blurSize)) * 0.05;\
   gl_FragColor = sum;\
}";


GraphicalFogOfWar::GraphicalFogOfWar(sf::RenderTarget *renderTarget, MapManager *mapManager, const Viewport *viewport)
	: renderTarget{renderTarget}, mapManager{mapManager}, viewport{viewport}
{
	const QSizeF size = mapManager->getMap()->getSize();
	QPointF sizeP{size.width(), size.height()};
	sizeP = viewport->fromMetresToPixels(sizeP);

	QPointF circleScale = viewport->getWholeScale();
	float maxScale = std::max(circleScale.x(), circleScale.y());
	circleScale /= maxScale;

	sizeScale = 1024.0f / std::max(sizeP.x(), sizeP.y());
	sizeP *= sizeScale;

	FOWTexture.create(sizeP.x(), sizeP.y());
	FOWTexture.clear(sf::Color::Black);
	FOWTexture.setSmooth(true);
	FOWSprite.setPosition(0, 0);

	FOWScreenTexture.create(1, 1);

	FOVTexture.create(1, 1);
	tempTexture.create(1, 1);

	circle.setPointCount(50);
	circle.setFillColor(sf::Color::Transparent);
	circle.setScale(circleScale.x(), circleScale.y());

	polygon.setFillColor(sf::Color::Black);

	blurHShader.loadFromMemory(blurH, sf::Shader::Fragment);
	blurVShader.loadFromMemory(blurV, sf::Shader::Fragment);
	// TODO zoom.
}


void GraphicalFogOfWar::update()
{
	const auto view = viewport->getCurrentView();
	const auto topLeft = viewport->fromMetresToPixels(view.topLeft());
	const auto bottomRight = viewport->fromMetresToPixels(view.bottomRight());
	// FOW
	auto *updateDiff = mapManager->getVisibilityUpdatesDiff();
	if (updateDiff->length() > 0 || view.toRect() != previousView.toRect()) {
		if (updateDiff->length() > 0) {
			drawUpdates(FOWTexture, *updateDiff, QRectF{0, 0, mapManager->getMap()->getSize().width(),
								mapManager->getMap()->getSize().height()}, sizeScale);
			FOWTexture.display();
		}

		enlargeAndBlur(FOWTexture.getTexture(), FOWScreenTexture, topLeft, bottomRight);
		FOWSprite.setPosition(topLeft.x(), topLeft.y());
		FOWSprite.setTexture(FOWScreenTexture.getTexture());

		// FOV
		// Clear previous visible region.
		FOVTexture.clear(sf::Color::Black);

		// Get and draw the current visible region.
		auto visibleRegion = mapManager->getVisibleRegion();
		drawUpdates(FOVTexture, visibleRegion, view, 1.0f);
		FOVTexture.display();
		FOVSprite.setTexture(FOVTexture.getTexture());
		FOVSprite.setPosition(topLeft.x(), topLeft.y());
		FOVSprite.setColor(sf::Color{255, 255, 255, 115});
	}
	delete updateDiff;
	previousView = view;
}


void GraphicalFogOfWar::draw()
{
	renderTarget->draw(FOVSprite);
	renderTarget->draw(FOWSprite, &blurHShader);
}


void GraphicalFogOfWar::drawUpdates(sf::RenderTexture &canvas, const VisibilityUpdateDiff &updateDiff,
                                    const QRectF &view, const float scale)
{
	QPointF scaledSize = viewport->fromMetresToPixels(view.bottomRight() - view.topLeft());
	if ((int)canvas.getSize().x < (int)scaledSize.x() || (int)canvas.getSize().y < (int)scaledSize.y()) {
		qDebug() << "Create!";
		canvas.create(scaledSize.x() * 1.2, scaledSize.y() * 1.2);
		canvas.clear(sf::Color::Black);
	}

	for (const auto &visUpdate: updateDiff) {
		const auto includeCircle = visUpdate.includeCircle;
		if (view.topLeft().x() - includeCircle.radius <= includeCircle.centre.x() &&
				view.topLeft().y() - includeCircle.radius <= includeCircle.centre.y() &&
				view.bottomRight().x() + includeCircle.radius >= includeCircle.centre.x() &&
				view.bottomRight().y() + includeCircle.radius >= includeCircle.centre.y()) {

			QPointF radiusP = {includeCircle.radius, includeCircle.radius};
			radiusP = viewport->fromMetresToPixels(radiusP) * scale;

			circle.setRadius(std::max(radiusP.x(), radiusP.y()));

			QPointF realPos = viewport->fromMetresToPixels(includeCircle.centre - view.topLeft()) * scale;
			circle.setPosition(0, 0);
			// Resize texture only when needed.
			auto bounds = circle.getGlobalBounds();
			if ((int)tempTexture.getSize().x < (int)(bounds.width + bounds.left) ||
					(int)tempTexture.getSize().y < (int)(bounds.height + bounds.top)) {
				tempTexture.create(bounds.width + bounds.left, bounds.height + bounds.top);
			}
			tempTexture.clear(sf::Color::Black);
			tempTexture.draw(circle, sf::RenderStates{sf::BlendMode::BlendMultiply});

			for (const BS::Geometry::Polygon &poly: visUpdate.ommitPolygons) {
				polygon.setPointCount(poly.length());

				for (int i = 0; i < poly.length(); ++i) {
					QPointF p = viewport->fromMetresToPixels(poly[i] - view.topLeft()) * scale -
							realPos + radiusP;
					polygon.setPoint(i, sf::Vector2f{(float)p.x(), (float)p.y()});
				}

				tempTexture.draw(polygon);
			}

			tempTexture.display();
			sf::Sprite tempSprite(tempTexture.getTexture());
			tempSprite.setPosition(realPos.x() - radiusP.x(), realPos.y() - radiusP.y());
			canvas.draw(tempSprite, sf::RenderStates{sf::BlendMode::BlendMultiply});
		}
	}
}


void GraphicalFogOfWar::enlargeAndBlur(const sf::Texture& texture, sf::RenderTexture& target, const QPointF& topLeft,
				       const QPointF& bottomRight)
{
	sf::Sprite shaderSprite;
	shaderSprite.setScale(1.0f / sizeScale, 1.0f / sizeScale);
	shaderSprite.setTexture(texture);
	shaderSprite.setTextureRect(sf::IntRect{(int)(topLeft.x() * sizeScale), (int)(topLeft.y() * sizeScale),
						(int)((bottomRight.x() - topLeft.x()) * sizeScale) + 1,
						(int)((bottomRight.y() - topLeft.y()) * sizeScale) + 1});
	shaderSprite.setPosition(0, 0);
	if ((int)target.getSize().x < (int)(bottomRight.x() - topLeft.x()) ||
			(int)target.getSize().y < (int)(bottomRight.y() - topLeft.y())) {
		target.create(bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y());
	}
	sf::RenderStates noBlendShader{sf::BlendMode::BlendNone};
	noBlendShader.shader = &blurVShader;
	target.draw(shaderSprite, noBlendShader);
	target.display();
}

