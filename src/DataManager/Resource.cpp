/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/Resource.hpp"


using std::size_t;


Resource::Resource(const char *data, const size_t &length)
	: data{data}, length{length}
{}


const char *Resource::getData() const
{
	return data;
}


const std::size_t Resource::getDataLength() const
{
	return length;
}
