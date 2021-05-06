#pragma once
#include "DMS.h"
#include <string>
#include <queue>
#include <iostream>

using namespace std;

namespace dms
{
	class Partition
	{
	protected:
		//partition needs to have a query and a server_num as the Partitions parameters
		IQuery* query;
		int server_num;
		Partition* nextp;
	
	
	public:
	
		Partition(int server_num, IQuery* query) {
			this->server_num = server_num;
			this->query = query;
		}
		string getPartition() { 
			cout << server_num << query << endl;
		
		}
		void getServer();
		string getQuery() { cout << query << endl; }
		void ServerPing(int server_num);
	};

	class TimingWheel 
	{
	protected:	
		//max_delay(max processing time of query);
		queue<IQuery*> queue;
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
		void insert(int processing_time, int server_num, Partition* p);
		void schedule();
		void clear_curr_slot(int current_slot);
		size_t nextIndex(int current_slot, int server_size);
		size_t ServerPing(int current_slot);
	};
}
