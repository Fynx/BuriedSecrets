/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "DataManager/Resource.hpp"


using std::size_t;


Resource::Resource(const ResourceType& type, const char* data, const size_t& length)
: type{type}, data{data}, length{length}
{
}


const char* Resource::getData() const
{
	return data;
}


const size_t Resource::getDataLength() const
{
	return length;
}


