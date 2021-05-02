#include "Partition.h"
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono_literals;
using namespace dms;

//TODO: schedule method, timer method, clear current slot method

void TimingWheel::schedule(DMS& dms) {

}

void TimingWheel::insert(int processing_time, int server_num, Query q)
{
	//this moves the timer wheel one slot
	++current_slot;
	//while the arbitrary server_num is available(1 on /0 off) and the slot isnt null push a query to the slot list 
	while (slot[current_slot].ServerPing() = true) {
		if (slot != nullptr) {
			slot[current_slot].push(q);
			cout << "pushing to slot:" << current_slot << endl;
		}
		//some kind of abstract "runtime" so the wheel can have a timer
		std::this_thread::sleep_for(10ms);
		//close the server close the thread
		server_num = 0;
	}
	
}
void TimingWheel::clear_curr_slot() 
{
	//the slot gets freed up of memory maybe ill use the memory.h or some kind of partition delete()
	slot = move(slot[current_slot] = null);

}

void Partition::ServerPing()
{
	//simulated server pinging if its available
	if (pair.first == server_num) 
	{
		cout << "server is not available" << endl;

	}
	else {
		server_num++;
		addPartition(server_num, *query);
	}

}

void Partition::addPartition(int server_num, Query query)
{
	//adds a query to the server num with pair 
	//its probably not that good but god help me
	pair.first = server_num;
	pair.second = query;

}
