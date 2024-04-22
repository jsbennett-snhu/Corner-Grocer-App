#include "GroceryItem.h"

GroceryItem::GroceryItem(std::string& name)
{
	this->name = name;
	this->quantity = 0;
}

GroceryItem::GroceryItem(std::string& name, int quantity)
{
	this->name = name;
	this->quantity = quantity;
}


std::string GroceryItem::getName() const
{
	return name;
}

int GroceryItem::getQuantity() const
{
	return quantity;
}


void GroceryItem::addUnit()
{
	quantity = quantity + 1;
}

void GroceryItem::removeUnit()
{
	if (quantity > 0) {
		quantity = quantity - 1;
	}
}


bool GroceryItem::operator<(const GroceryItem& other) const
{
	return name.compare(other.getName()) < 0;
}
