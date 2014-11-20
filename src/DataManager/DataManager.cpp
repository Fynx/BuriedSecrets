#include "DataManager/DataManager.hpp"
#include "DataManager/FileIO.hpp"

DataManager::DataManager()
{
	loadPrototypes();
}

DataManager::~DataManager()
{
	qDeleteAll(prototypes);
}

const Prototype *DataManager::getPrototype(const QString &name) const
{
	return prototypes[name];
}

void DataManager::loadPrototypes()
{
	Prototype *p = new Prototype();

	loadFromFile("prototypeFile", *p);

	p->setProperty("name", "ItsATrap");

	prototypes["ItsATrap"] = p;
}
