#pragma once
#include "DMS.h"
#include <string>
#include <pair>

using namespace dms;
using namespace std;
class Partition
{
protected:
	//partition needs to have a query and a server_num holding the query and how much processing time it takes i think
	DMS dms;
	Query* query;
	int server_num;
	Partition* nextp;
	pair<int, Query> pair;

	
	Partition() = default;

public:
	string getPartition() { 
		static Partition* nextp;
		
	}
	void getServer();
	void getQuery();
	void ServerPing();
	void addPartition(int server_num, Query query);


};

class TimingWheel 
{
protected:	
	//max_delay(max processing time of query);
	int current_slot = 0;
	static const int max_delay = 6;

	Partition* slot[max_delay + 1];

public:
	void insert(int processing_time,  int server_num, Query q);
	void schedule(DMS& dms);
	void clear_curr_slot();
};
class Timer
{
	TimingWheel();
		~TimingWheel();
	vector<Timer*> slots;
	Timer* addtimer();
	
	void deltimer();
	void tick();
	

};
