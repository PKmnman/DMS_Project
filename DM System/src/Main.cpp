// Filename: Main.cpp
// Author: Gary Reeves
// Date: 01/04/2021
// Compiler Used: MSVC

#include <iostream>
#include "DMS.h"
#include "Menu.h"
#include "Partition.h"

using namespace std;
using namespace dms;
using namespace menu;


void search()
{
	// Get input
	string in;
	cout << "Please input the name of your Search Query:" << endl;
	getline(cin, in);

	// Construct the search query
	SearchQuery query(in);

	// Get the result
	vector<Contact*> result = query();

	// Return on no results found
	if (result.empty()) return;

	// Else, call the display function for each contact
	for (auto r : result) r->display();
}


void display()
{
	// Get the name of the contact to display
	string in;
	cout << "Please input the name of the contact to display: ";
	getline(cin, in);

	// Construct the display query
	DisplayQuery display(in);

	// Perform the query on the DMS
	display();
}


void partition()
{
	// Construct a TimeWheel object
	TimeWheel peanut(5);
	cout << "Starting TimeWheel" << endl;

	// Populate the DMS with some queries
	DMS::getDMS().registerQuery(new DisplayQuery("Freya McDaniel"));
	DMS::getDMS().registerQuery(new DisplayQuery("Jada Foster"));
	DMS::getDMS().registerQuery(new DisplayQuery("Ruth Wilkinson"));
	DMS::getDMS().registerQuery(new DisplayQuery("Dana White"));
	DMS::getDMS().registerQuery(new DisplayQuery("Joshua Berry"));
	DMS::getDMS().registerQuery(new DisplayQuery("Freya McDaniel"));
	DMS::getDMS().registerQuery(new DisplayQuery("Freya McDaniel"));
	DMS::getDMS().registerQuery(new DisplayQuery("Freya McDaniel"));
	DMS::getDMS().registerQuery(new DisplayQuery("Freya McDaniel"));
	DMS::getDMS().registerQuery(new DisplayQuery("Freya McDaniel"));


	peanut.schedule();
}


int main()
{
	// Create a Menu object
	Menu menu("DMS Program", "To navigate, input commands located in square brackets.\nAll commands are lowercase.");

	// Load date to the DMS
	cout << "Starting DMS..." << endl;
	DMS::getDMS().loadData("Input.txt");
	cout << "DMS Loaded From File" << endl << endl;

	// Add menu options
	menu.addOption("Search the DMS", "search", search);
	menu.addOption("Display a contact", "display", display);
	menu.addOption("Perform Partition/TimingWheel Routine", "timewheel", partition);

	// Run the menu
	menu.display();
}
