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
}