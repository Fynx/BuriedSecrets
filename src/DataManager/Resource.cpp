/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "DataManager/Resource.hpp"


using std::size_t;


Resource::Resource(const char *data, const size_t &length)
	: data{new char [length]}, length{length}
{
	memcpy(this->data, data, length);
}


Resource::~Resource()
{
	delete data;
}


const char *Resource::getData() const
{
	return data;
}


const std::size_t Resource::getDataLength() const
{
	return length;
}
