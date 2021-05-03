#pragma once
#include <map>
#include <vector>
#include <string>
#include <regex>
#include <functional>

#include "Contact.h"


namespace dms
{
	using namespace std;

	using namespace contact;

	// Compile-time constants for file reading
	
	constexpr unsigned int NAME_FIELD = 1;
	constexpr unsigned int GENDER_FIELD = 2;
	constexpr unsigned int PHONE_FIELD = 3;
	constexpr unsigned int EMAIL_FIELD = 4;

	constexpr unsigned int LADDRESS_FIELD = 5;
	constexpr unsigned int SADDRESS_FIELD = 6;

	constexpr unsigned int DISTRICT_FIELD = 7;
	constexpr unsigned int STATE_FIELD = 8;
	constexpr unsigned int ZIPCODE_FIELD = 9;
	
	class Query;
	
	class DMS
	{
		// Storage for contacts

		map<string, Query*> queries;

		vector<Contact*> contacts;
		
		

	public:

		DMS() = default;
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
		void addPersonalContact(std::string contact);
		void addBusinessContact(std::string contact);
		void displayQuery();
		// Function to load contact data from file
		void loadData(const string& filepath);
	};

	
	class Query
	{
		
	public:

		virtual vector<Contact*> operator ()(DMS& target);
		
		string getQuery(){return string();}

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