#pragma once
#include "DMS.h"
#include <string.h>

using namespace dms;
using namespace std;
class Partition
{
private:

	DMS dms;
	Query* query;
	int Server_num;
	Partition* nextp;
	Partition() {
		nextp;
	}

public:
	//all needed accessor function
	string getPartition() { 
		static Partition* nextp;
		
	}
	void getServer();
	void getQuery();
	void ServerPing();

};

class TimingWheel 
{
private:
	Partition* slot[max_delay + 1];
	//max_delay(max processing time of query);
	int current_slot = 0;

public:
	void insert(int processing time, Server_num, Query q);
	void schedule(DMS& dms);
	void clear_curr_slot();
};
