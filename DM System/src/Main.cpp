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
	
	menu.setTitle(":Main Menu:");
	menu.addOption("startDMS", load);
	menu.addOption("searchQuery", search);
	menu.addOption("displayQuery",display);
	menu.addOption("Partition/TimingWheel", partition);


}

void load() {
	DMS dms;
	dms.loadData("input.txt");
}
void search() {
	DMS dms;
	dms.loadData("input.txt");
	dms.searchNumJohn();
}
void display() {
	DMS dms;
	dms.loadData("input.txt");
	DisplayQuery display("john");
}
void partition() {
	TimingWheel peanut;
	peanut.schedule();
}