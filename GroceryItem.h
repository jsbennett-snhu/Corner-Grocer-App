#pragma once
#include <string>
using namespace std;


class GroceryItem
{
public:

	//Constructor for Grocery Item without a quantity
	GroceryItem(string& name);
	//Constructor for Grocery item with both name and quantity
	GroceryItem(string& name, int quantity);

	//Gets the name of the current GroceryItem
	//@returns - the name of the GroceryItem as a string
	string getName() const;
	//Gets the quantity of the current GroceryItem
	//@returns - the quantity as an integer
	int getQuantity() const;

	//Adds 1 to the qauntity of the current GroceryItem
	void addUnit();
	//Subtracts 1 from the qauntity of the current GroceryItem
	void removeUnit();

	//Overides the comparison < opoerator when comparing two GroceryItems.
	//@param other - the other GroceryItem to compare with
	//@returns - true if the name of the invoking GroceryItem is 
	//lexicographically less than the name of the given GroceryItem
	bool operator<(const GroceryItem& other) const;

private:
	string name;
	int quantity;

};

