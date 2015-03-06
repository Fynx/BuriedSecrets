/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/Entities/Animation.hpp"


Animation::Animation(const Animation::FramesList &frames)
: frames{frames}
{}


Animation::Animation(Animation::FramesList &&frames)
: frames{std::move(frames)}
{}


const sf::Texture *Animation::getFrame(const int direction, const int id) const
{
	return frames.at(direction).at(id);
}
