#include "DataManager/DataManager.hpp"
#include "GameObjects/Equipment.hpp"

class ItemConstructor {

public:
	ItemConstructor(DataManager *);
	QList<Prototype *> possibleItems(Equipment *eq = nullptr);
	Item *constructItem(Prototype *, Equipment *eq);

private:
	QList<Prototype *> allItems;
};
