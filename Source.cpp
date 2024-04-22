// Author: Justin Benentt
// Class: CS-210
// Assignment: Project 3
// Date: 4/21/2024

#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <string>
#include <stdexcept>
#include "GroceryItem.h"
using namespace std;



//Switches between 4 different screen states based on user input until the user chooses to quit
//@returns - Error status of the program 
int main();

//Creates a set of Grocery Items from inventory.txt and backs it up in frequency.dat
//@returns - the generated set of Grocery Items
set<GroceryItem> readInventory();

//Performs a few operations to clear the input output stream for use after an error has occured
void cleanIOS();

//Prints a list of Grocery Items and thier frequencies from a given set of Grocery Items
//@param itemList - The set of Grocery Items to print out to the user
void printItemList(set<GroceryItem> itemList);

//Prints a list of Grocery Items and thier frequencies from a given set of Grocery Items as a Histogram
//@param itemList - The set of Grocery Items to build into a Histogram
void printItemGraph(set<GroceryItem> itemList);

//Searches through a given set of Grocery Items for a user selected item and prints it's frequency
//@param itemList - The set of Grocery Items to search through
void searchItemList(set<GroceryItem> itemList);



int main () {
	cin.exceptions(ios::failbit);

	// Variable to control the main loop and also determines which screen the loop should display
	int currScreen = 0;
	// This string is changed if the user makes invalid input
	string menuPrompt = " What would you like to do?  ";

	// Run the main menu screen and sub menu's until the chooses to quit
	while (currScreen != 4) {

		// Diffrent screen states: Main Menu = 0, Search = 1, List = 2, Graph = 3, Default = Error
		switch (currScreen) {

			//MAIN MENU: prints the main menu then gets and validates user input. Changes the screen state based on user input.
			case 0: {
				cout << "*************************************" << endl;
				cout << "************ MAIN MENU **************" << endl << endl;
				cout << setw(10) << right << "[1]" << "Search an item" << endl;
				cout << setw(10) << right << "[2]" << "List item frequencies" << endl;
				cout << setw(10) << right << "[3]" << "Graph item frequencies" << endl;
				cout << setw(10) << right << "[4]" << "Quit" << endl << endl;
				cout << "     " << menuPrompt << endl;

				int userChoice = 0;

				try {
					cin >> userChoice;
					
					if (!((userChoice >= 1) && (userChoice <= 4))) {
						throw runtime_error("Choice must be between 1 & 4.");

					}
					else {
						currScreen = userChoice;
						menuPrompt = " What would you like to do?  ";
					}
				}
				catch (ios_base::failure& e) {		//If the user inputs invalid input set the prompt for the menu
					menuPrompt = " Input can only be a number. ";
				}
				catch (const runtime_error& err) {	//IF the user inputs a number out of range set the prompt for the menu
					menuPrompt = err.what();
				}
				system("cls");
				cleanIOS();
				continue;
			}

			//SEARCH: Creates and Searches a set of Grocery Items for a user inputted item, then displays it's frequency
			case 1: {
				set<GroceryItem> itemList;
				itemList = readInventory();
				searchItemList(itemList);
				break;
			}
			
			//LIST: Creates and lists a set of Grocery Items with each of their frequencies
			case 2: {
				set<GroceryItem> itemList;
				itemList = readInventory();
				printItemList(itemList);
				break;

			}
			//GRAPH: Creates and lists a set of Grocery Items and their frequencies in the form of a histogram
			case 3: {
				set<GroceryItem> itemList;
				itemList = readInventory();
				printItemGraph(itemList);
				break;
			}

			//ERROR: Program should never end up here but just in case
			default: {
				cout << "Error: Invalid screen state" << endl << "The program will now close" << endl;
				return 1;
			}
		}

		//Prompts the user to return to the main menu when they're ready then takes them back when they input anything
		cout << "   Enter any key to continue . . .";
		string userInput;
		cin >> userInput;
		system("cls");
		currScreen = 0;

	}
	return 0;
}

set<GroceryItem> readInventory() {


	ifstream inFS;
	inFS.open("inventory.txt"); //This file is updated by an external source. We read this to create our set.

	if (!inFS.is_open()) {
		throw runtime_error("[ Could not open file inventory.txt ]");
	}

	set<GroceryItem> items;

	//Until we reach the end of the file
	while (!inFS.eof()) {
		string name;
		int amount;
		getline(inFS, name);

		//This section is heavily commented to make sure I understand what is happening.
		//Establishes a pointer to a new memory location and stores a new GroceryItem there.
		GroceryItem* newItem = new GroceryItem(name);
		//Searches through the set as it is currently for a Grocery item of the same name.
		auto existingItem = items.find(*newItem);

		//If the grocery item was found, copy the name and quantity of the older item to our new item on the heap.
		//Then erase the older item from the list
		if (existingItem != items.end()) {
			name = existingItem->getName();
			amount = existingItem->getQuantity();
			items.erase(existingItem);
			*newItem = GroceryItem(name, amount);
		}

		//Add 1 Unit to the new GroceryItems quantity and insert it into the set.
		//Afterward delete the allocated memory location
		newItem-> addUnit();
		items.insert(*newItem);
		delete newItem;
	}

	inFS.close();

	ofstream outFS;
	outFS.open("frequency.dat"); //This file is for storing a back up of all items and their frequencies.

	if (!outFS.is_open()) {
		throw runtime_error("[ Could not open file frequency.dat ]");
	}

	for (GroceryItem item : items) {
		outFS << item.getQuantity() << " " << item.getName() << endl;
	}

	outFS.close();

	//retruns the generated set of Grocery Items
	return(items);
}

void cleanIOS() {
	cin.clear();
	string remainingText;
	getline(cin, remainingText);
}

void printItemList(set<GroceryItem> itemList)
{
	cout << "*************************************" << endl;
	cout << "************ LIST ITEMS *************" << endl << endl;

	// Variables for padding the text output based on size. 
	int nameBufferSize = 31;
	int quantityBufferSize = 0;

	// Gets the length of the largest item quantity within the set
	for (GroceryItem item : itemList) {
		int quantity = to_string(item.getQuantity()).length();

		if (quantityBufferSize < quantity) {
			quantityBufferSize = quantity;
		}
	}

	//Adjust the name buffer based on the size of the quantity buffer
	nameBufferSize = nameBufferSize - quantityBufferSize; 

	for (GroceryItem item : itemList) {
		string name = item.getName();
		int quantity = item.getQuantity();
		cout << setw(nameBufferSize) << left << name;
		cout << "  x  ";
		cout << setw(quantityBufferSize) << right << quantity << endl;
	}

	cout << endl;
}

void printItemGraph(set<GroceryItem> itemList)
{
	cout << "*************************************" << endl;
	cout << "*********** GRAPH ITEMS *************" << endl << endl;

	// Variable for padding the text output based on size. 
	int bufferSize = 0;

	//Gets the length of the longest name in the set
	for (GroceryItem item : itemList) {
		int nameLength = item.getName().length();

		if (bufferSize < nameLength) {
			bufferSize = nameLength;
		}

	}	

	//Formats and prints the histogram
	for (GroceryItem item : itemList) {
		string name = item.getName();
		int quantity = item.getQuantity();
		cout << setw(bufferSize) << left << name;
		cout << " | ";

		for (int i = 1; i <= quantity; ++i) {
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
}

void searchItemList(set<GroceryItem> itemList)
{
	string itemName = "";

	//Until the user has entered an item, prompt the user for an item.
	while (itemName == "") {
		cout << "*************************************" << endl;
		cout << "************** SEARCH ***************" << endl;
		cout << "         Search for any item         " << endl << endl;

		itemName;
		cin >> itemName;
		system("cls");
	}

	// Searches for the item within the set and displays the frequency of the item.
	// If no item is found it simply displays a frequency of 0
	cout << "*************************************" << endl;
	cout << "************** SEARCH ***************" << endl;
	cout << "         Search for any item         " << endl << endl;
	cout << setw(31) << left << itemName << "  x ";

	for (GroceryItem item : itemList) {

		string name = item.getName();
		int quantity = item.getQuantity();

		if (itemName == item.getName()) {
			cout << quantity << endl << endl;
			return;
		}
	}

	cout << "0" << endl << endl;


}
