#pragma once
#include <map>
#include <vector>
#include <string>

#include <functional>
#include <varargs.h>

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
		
		
		// Function to register a query to the DMS
		void registerQuery(Query* const query_func);
		
		// Fuction to load contact data from file
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