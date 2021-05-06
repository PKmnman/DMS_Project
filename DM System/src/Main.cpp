#include "Contact.h"
#include "DMS.h"
#include "Partition.h"
#include "Menu.h"
#include <iostream>

using namespace std;
using namespace dms;
using namespace menu;

int main()
{
	Menu menu;
	DMS dms;
	std::string input;
	menu.setTitle(":Main Menu:");
	cout << "please select an option:" << endl;
	menu.addOption("startDMS", load);
	menu.addOption("searchQuery", search);
	menu.addOption("displayQuery", display);
	menu.addOption("Partition/TimingWheel", partition);
	cin >> input;
	menu.select(input);
	
	DMS::dms;
	dms.loadData();
	DMS::getDMS();
}

void load() {
	cout << "Starting DMS.." << endl;;
	DMS dms = DMS::getDMS();
	cout << "DMS Loaded From File" << endl;
	main();
}
void search() {
	DMS dms;
	string in;
	dms.loadData("Input.txt");
	cout << "Please input the name of your Search Query:" << endl;
	cin >> in;
	DisplayQuery query(in);
	
}
void display() {
	DMS dms;
	string in;
	dms.loadData("Input.txt");
	cout << "Please input the name of your Query:" << endl;
	cin >> in;
	DisplayQuery display(in);
}
void partition() {
	DMS dms;
	TimingWheel peanut(10);
	cout << "Starting TimeWheel" << endl;
	peanut.schedule();
}