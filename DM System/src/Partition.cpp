#include "Partition.h"
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono_literals;
using namespace dms;

//TODO: schedule method, Partition Queue

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
	return (current_slot + 1) % server_size;
}

void TimingWheel::schedule() {

	//make function fillQueue with partitions
	IQuery* q;
	queue.push(q);
	//a loop for an array where it pings the arbitrary server and inserts if it is empty
	while(queue.front()) {
		for (int current_slot = 0; true; nextIndex(current_slot, server_size))
		{
			if (ServerPing(current_slot)) {

				//insert(10, int(current_slot), q);
				queue.pop();
			}
			/*if (ServerPing(current_slot) is full after first loop{
				clear_curr_slot(current_slot);
			}*/
			if (queue.front() = nullptr)
			{
				break;
			}

		}
	}
}

void TimingWheel::insert(int processing_time, int server_num, Partition* q)
{
	//adds a partition to the slot on the timing wheel
	
	server[server_num] = q;

	std::this_thread::sleep_for(chrono::milliseconds(processing_time));
	cout << "Partition pushed to server: " + server_num << endl;

	
}
void TimingWheel::clear_curr_slot(int current_slot) 
{
	//the slot gets freed up of the IQuery object
	server[current_slot] = nullptr;

}

