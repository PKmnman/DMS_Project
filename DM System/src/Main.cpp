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
	DisplayQuery display("john");
}


void partition() {
	DMS dms;
	TimeWheel peanut(10);
	cout << "Starting TimeWheel" << endl;
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
	menu.addOption("Perform Partition/TimingWheel Routine", "timingwheel", partition);

	// Run the menu
	menu.display();

}

