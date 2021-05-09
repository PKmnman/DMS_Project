// Filename: Partition.h
// Author: Juan Barreto Rodriguez
// Date: 05/05/2021
// Compiler Used: MSVC

#ifndef PARTITION_H
#define PARTITION_H
#include <iostream>
#include <queue>
#include <string>
#include "DMS.h"

using namespace std;

namespace dms
{
	class Partition
	{
	private:
		//partition needs to have a query and a server_num as the Partitions parameters
		IQuery* query;
		int server_num;
		Partition* nextp;
		queue<IQuery*> que;


	public:
		Partition(int server_num, IQuery* query)
		{
			this->server_num = server_num;
			this->query = query;
		}


		string getPartition()
		{
			cout << server_num << query << endl;
		}


		void getQuery();
		void getServer();
		vector<Contact*> operator()();

		void ServerPing(int server_num);
	};


	class TimeWheel
	{
	private:
		queue<IQuery*> que;
		vector<IQuery*> queries;
		static const int max_delay = 6;
		Partition** server;
		int server_size;

	public:
		int current_slot;


		TimeWheel(int size)
		{
			current_slot = 0;
			server = new Partition*[size];
			this->server_size = size;
			for (int i = 0; i < size; i++)
			{
				server[i] = nullptr;
			}
		}


		void fillQueue();
		vector<IQuery*> getQuerys();
		void insert(int processing_time, size_t server_num, Partition* p);
		void schedule();
		void clear_curr_slot(int current_slot);

		size_t nextIndex(size_t& slot, int server_size);
		size_t ServerPing(size_t& slot);
	};
}
#endif
