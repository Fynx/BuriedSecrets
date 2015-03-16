/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <cstddef>
#include <QtCore/QString>


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