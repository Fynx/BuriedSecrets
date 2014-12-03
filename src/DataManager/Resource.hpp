/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <cstddef>


enum class ResourceType {
	Texture,
	Font
};


class Resource {
public:
	Resource(const ResourceType &type, const char *data, const std::size_t &length);
	const char *getData() const;
	const std::size_t getDataLength() const;

private:
	const ResourceType type;
	const char *data;
	const std::size_t length;
};