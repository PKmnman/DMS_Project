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

size_t TimeWheel::ServerPing(size_t& slot)
{
	//simulated server pinging
	//top is unavailable, bottom is free
	if (server[slot]) 
	{
		
		cout << "server: " << slot << " is not available" << endl;
		nextIndex(slot, server_size);

	}
	else
	{
		return true;
	}

}

size_t TimeWheel::nextIndex(size_t& slot, int server_size)
{
	//looping the timewheel server array
	return ((++slot) % server_size);
}

vector<Contact*> Partition::operator()()
{
	return (*query)();
}

void TimeWheel::fillQueue() {
	//Fill the queue with queries List
	vector<IQuery*> dmsQueries = DMS::getDMS().getQueries();
	for (int i = 0; i < dmsQueries.size(); i++) {
		
		que.push(dmsQueries[i]);
	
	}
	
}

vector<IQuery*> TimeWheel::getQuerys() {
	//get Queries list from DMS
	return  DMS::getDMS().getQueries();
}

void TimeWheel::schedule() {

	fillQueue();
	
	//a loop for an array where it pings the arbitrary server and inserts if it is empty if it not empty it move to the next one

	for (size_t current_slot = 0; !que.empty(); current_slot = nextIndex(current_slot, server_size-1))
	{
		if (ServerPing(current_slot)) {

			IQuery* banana = que.front();
			//(*banana)();

			insert(10, current_slot, new Partition(current_slot, banana));
			que.pop();

		}
		//Tick for each used up slot of the wheel it clears when 10 seconds have passed;
		for (int j = 0; j < 9; ++j)
		{
			//arbitrary query runtime
			std::cout << "tick.\n" << std::flush;
			std::this_thread::sleep_for(10ms);
			
			//before the timer ends display the Query then clear the slot
				

			
		}
		
		(*server[current_slot])();
		clear_curr_slot(current_slot);
		cout << "Query Finished at slot: " << current_slot << endl;
	
	}
}

void TimeWheel::insert(int processing_time, int server_num, Partition* q)
{
	//adds a partition to the slot on the timing wheel
	
	server[server_num] = q;

	std::this_thread::sleep_for(chrono::milliseconds(processing_time));
	cout << "Partition pushed to server: " << to_string(server_num) << endl;

	
}

void TimeWheel::clear_curr_slot(int current_slot) 
{
	//the slot gets freed up of the IQuery object
	server[current_slot] = nullptr;

}

