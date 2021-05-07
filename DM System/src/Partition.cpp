#include "Partition.h"
#include "Query.h"
#include <thread>
#include <chrono>
#include <queue>
#include <iostream>

using namespace std;
using namespace chrono_literals;
using namespace dms;

//TODO: schedule method, Partition Queue

size_t TimeWheel::ServerPing(int current_slot)
{
	//simulated server pinging
	//top is unavailable, bottom is free
	if (server[current_slot]) 
	{
		
		cout << "server: " + current_slot << " is not available" << endl;
		nextIndex(current_slot, server_size);

	}
	else
	{
		return true;
	}

}

size_t TimeWheel::nextIndex(int current_slot, int server_size)
{
	//looping the timewheel server array
	return (current_slot + 1) % server_size;
}

void TimeWheel::fillQueue() {
	//Fill the queue with queries List
	vector<IQuery*> dmsQueries = DMS::getDMS().getQueries();;
	for (int i = 0; i < dmsQueries.size(); i++) {
		
		que.push(dmsQueries[i]);
	
	}
	
}

vector<IQuery*> TimeWheel::getQuerys() {
	//get Queries list from DMS
	return  DMS::getDMS().getQueries();
}

void TimeWheel::schedule() {

	TimeWheel::fillQueue();
	//a loop for an array where it pings the arbitrary server and inserts if it is empty if it not empty it move to the next one
	while(!que.empty()) {
		for (int current_slot = 0; true; nextIndex(current_slot, server_size-1))
		{
			if (ServerPing(current_slot)) {

				IQuery* banana = que.front();

				insert(10, current_slot, new Partition(current_slot, banana));
				que.pop();
				delete banana;

			}
			//Tick for each used up slot of the wheel it clears when 10 seconds have passed;
			for (int j = 0; j < 10; ++j)
			{
				std::cout << "tick.\n" << std::flush;
				std::this_thread::sleep_for(10ms);
				if (j == 9) {
					DisplayQuery("Freya McDaniel")();
					clear_curr_slot(current_slot);
				}
			}
		
		}
	}
}

void TimeWheel::insert(int processing_time, int server_num, Partition* q)
{
	//adds a partition to the slot on the timing wheel
	
	server[server_num] = q;

	std::this_thread::sleep_for(chrono::milliseconds(processing_time));
	cout << "Partition pushed to server: " + server_num << endl;

	
}

void TimeWheel::clear_curr_slot(int current_slot) 
{
	//the slot gets freed up of the IQuery object
	server[current_slot] = nullptr;

}

