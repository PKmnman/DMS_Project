#pragma once
#include <map>
#include <vector>
#include <string>

#include <functional>

#include "Contact.h"

// TODO: Part 2 - Designing the DMS System
namespace dms
{
	using namespace std;

	class Query;
	
	class DMS
	{
		// Storage for contacts

		map<string, Query*> queries;

		vector<Contact*> contacts;
		
		DMS() = default;

	public:

		static DMS& getDMS()
		{
			static DMS* dms;

			if(dms)
			{
				return *dms;
			}
			else
			{
				dms = new DMS();
				return *dms;
			}
		}
		
		void addContact(Contact& contact);

		void removeContact(string& name);

		map<string&, int> search();
		
		// Function to register a query to the DMS
		void registerQuery(string& key, Query* const query_func);
		
		// Function to load contact data from file
		void loadData(const string& filepath);
	};

	
	class Query
	{
		
	public:

		virtual vector<Contact*> operator ()(DMS& target);

	};


	class SearchQuery : public Query
	{
	public:
		virtual vector<Contact*> operator()(DMS& target) override;
	};

	
	class DisplayQuery : public Query
	{
	public:
		virtual vector<Contact*> operator()(DMS& target) override;
	};
}