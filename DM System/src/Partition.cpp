// Filename: Partition.cpp
// Author: Juan Barreto Rodriguez
// Date: 05/05/2021
// Compiler Used: MSVC

#include "Partition.h"
#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include "Query.h"

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
	cout << "Server Number: " << server_num << " ";
	return (*query)();
}


void TimeWheel::fillQueue()
{
	//Fill the queue with queries List
	vector<IQuery*> dmsQueries = DMS::getDMS().getQueries();
	for (int i = 0; i < dmsQueries.size(); i++)
	{
		que.push(dmsQueries[i]);
	}
}


vector<IQuery*> TimeWheel::getQuerys()
{
	//get Queries list from DMS
	return DMS::getDMS().getQueries();
}


void TimeWheel::schedule()
{
	fillQueue();

	//a loop for an array where it pings the arbitrary server and inserts if it is empty if it not empty it move to the next one

	for (size_t current_slot = 0; !que.empty(); current_slot = nextIndex(current_slot, server_size - 1))
	{
		//if (ServerPing(current_slot)) {

		IQuery* banana = que.front();
		//(*banana)();

		insert(10, current_slot, new Partition(current_slot, banana));
		que.pop();

		//}

		//Tick for arbitrary time  it clears when 10 seconds have passed;
		for (int j = 0; j < 9; ++j)
		{
			//arbitrary query runtime
			std::cout << "." << std::flush;
			std::this_thread::sleep_for(10ms);
		}
		cout << endl;

		//when the timer breaks display the query and then clear the slot of the query;
		(*server[current_slot])();
	}
}


void TimeWheel::insert(int processing_time, size_t server_num, Partition* q)
{
	//adds a partition to the slot on the timing wheel
	if (ServerPing(server_num))
	{
		server[server_num] = q;

		std::this_thread::sleep_for(chrono::milliseconds(processing_time));
		cout << "Partition pushed to server: " << to_string(server_num) << endl;
	}
	else
	{
		clear_curr_slot(static_cast<int>(server_num));
		cout << "Query Finished at slot: " << static_cast<int>(server_num) << endl;
	}
}


void TimeWheel::clear_curr_slot(int current_slot)
{
	//the slot gets freed up of the IQuery object
	server[current_slot] = nullptr;
}
