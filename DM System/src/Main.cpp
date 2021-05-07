#include "DMS.h"
#include "Partition.h"
#include "Menu.h"
#include <iostream>

using namespace std;
using namespace dms;
using namespace menu;


void search() {
	DMS dms = DMS::getDMS();
	string in;
	cout << "Please input the name of your Search Query:" << endl;
	getline(cin, in);
	SearchQuery query(in);

	vector<Contact*> result = query();
	
	if(result.empty())
	{
		cout << "No results found..." << endl;
		return;
	}
	
	for(auto r : result)
	{
		r->display();
	}
}


void display() {
	string in;
	cout << "Please input the name of the contact to display: ";
	getline(cin, in);
	
	DisplayQuery display(in);

	display();
}


void partition() {
	TimeWheel peanut(5);
	cout << "Starting TimeWheel" << endl;
	DMS::getDMS().getQueries();
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
	cout << "DMS Loaded From File" << endl;

	// Add menu options
	menu.addOption("Search the DMS", "search", search);
	menu.addOption("Display a contact", "display", display);
	menu.addOption("Perform Partition/TimingWheel Routine", "timewheel", partition);

	// Run the menu
	menu.display();

}

