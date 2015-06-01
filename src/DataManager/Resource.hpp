/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <cstddef>
#include <QtCore/QString>


/**
 * @brief Represents a simple resource storing raw data.
 *
 * It is used for loading textures, fonts etc. as raw data to be passed to correct, more specific data managers.
 */
class Resource {
public:
	Resource(const char *data, const std::size_t &length);
	~Resource();
	const char *getData() const;
	const std::size_t getDataLength() const;

private:
	char *data;
	const std::size_t length;
};
