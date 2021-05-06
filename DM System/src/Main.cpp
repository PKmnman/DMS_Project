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


}

void load() {
	cout << "Starting DMS.." << endl;;
	DMS dms;
	dms.loadData("input.txt");
	cout << "DMS Loaded From File" << endl;
	main();
}
void search() {
	DMS dms;
	string in;
	dms.loadData("input.txt");
	cout << "Please input the name of your Search Query:" << endl;
	cin >> in;
	dms.getQuery(in);
	
}
void display() {
	DMS dms;
	dms.loadData("input.txt");
	DisplayQuery display("john");
}
void partition() {
	TimingWheel peanut(10);
	peanut.schedule();
}