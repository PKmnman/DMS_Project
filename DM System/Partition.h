#pragma once
#include "DMS.h"
#include <string>

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
	
	Partition() = default;

public:
	string getPartition() { 
		cout << server_num << query.getQuery();
		
	}
	void getServer();
	void getQuery();
	void ServerPing(int server_num);
	void addPartition(int server_num, Query query);


};

class TimingWheel 
{
protected:	
	//max_delay(max processing time of query);
	
	static const int max_delay = 6;
	Partition** server;
	int server_size = sizeof(server) / sizeof(server[0]);
	
public:
	int current_slot;
	TimingWheel(int size)
	{
		server = new Partition*[size];
		for (int i = 0; i < size; i++) {
			server[i] = nullptr;
		}
	}
	void insert(int processing_time, int server_num, Query q);
	void schedule(DMS& dms, int server[10]);
	void clear_curr_slot();
	size_t nextIndex(int current_slot, int server_size);
	size_t ServerPing(int current_slot);
};
class Timer
{
	TimingWheel();
	vector<Timer*> slots;
	Timer* addtimer();
	void deltimer();
	void tick();
	

};
