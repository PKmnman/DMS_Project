#include "Contact.h"
#include "DMS.h"
#include "Partition.h"
#include <fstream>

using namespace dms;
using namespace dms::contact;

int main()
{
	DMS dms;
	dms = DMS::getDMS();
	//DMS::getDMS();
	dms.loadData("input.txt");
	DisplayQuery display("john");
}
void partition() {
	TimingWheel peanut(10);
	peanut.schedule();
}