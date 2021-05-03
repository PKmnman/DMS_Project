#include "Partition.h"
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono_literals;
using namespace dms;

//TODO: schedule method, timer method, clear current slot method

size_t TimingWheel::ServerPing(int current_slot)
{
	//simulated server pinging
	//top is unavailable, bottom is free
	if (server[current_slot]) 
	{
		nextIndex(current_slot, server_size);
		cout << "server: " + current_slot << " is not available" << endl;

	}
	else
	{
		return true;
	}

}
size_t TimingWheel::nextIndex(int current_slot, int server_size)
{
	//looping the timewheel server array
	current_slot = (current_slot + 1) % server_size;
}

void Partition::addPartition(int server_num, Query query)
{
	//adds a query to the server num with pair 
	


}
void TimingWheel::schedule(DMS& dms,Query server[7]) {

	Query q = dms.getQuery();
	
	
	//a loop for an array where it pings the arbitrary server a
	for (int current_slot = 0; true; nextIndex(current_slot, server_size))
	{
		if (ServerPing(current_slot)) {
			
			insert(10,int(current_slot), q);
		}
		else {

		}
		

	}
}

void TimingWheel::insert(int processing_time, int server_num, Query q)
{
	//adds a partition to the slot on the timing wheel
	Partition* p = new Partition;
	p.addPartition(server_num, q);
	std::this_thread::sleep_for(chrono::milliseconds(processing_time));
	cout << "Partition pushed to server: " + server_num << endl;
	
}
void TimingWheel::clear_curr_slot() 
{
	//the slot gets freed up of the Query object
	server[current_slot]

}


