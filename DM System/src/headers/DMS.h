#ifndef DMS_H
#define DMS_H

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
		
		void init();

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

		map<string&, int> searchNumJohn();
		
		// Function to register a query to the DMS
		void registerQuery(const string& key, Query* const query_func);

		template <typename T>
		T* getQuery(const string& name)
		{
			Query* query = queries.at(name);
			return static_cast<T*>(query);
		}

		/*Query* getQuery(const string& name)
		{
			return queries.at(name);
		}*/

		void addPersonalContact(std::string contact);
		void addBusinessContact(std::string contact);
		
		// Function to load contact data from file
		void loadData(const string& filepath);

		const vector<Contact*> getContacts() const { return contacts; }

		
	};

	
	class Query
	{
	protected: 
		string name;

		Query(const string& name) : name(name) {};

	public:

		virtual vector<Contact*> operator ()();
		
		string getQuery(){return string();}

	};


	class SearchQuery : public Query
	{
	public:

		virtual vector<Contact*> operator()() override;
	};

	
	class DisplayQuery : public Query
	{

		string target;

	public:

		DisplayQuery() : Query("Display") {}

		DisplayQuery(const string& target) : Query("Display")
		{
			this->target = target;
		}

		virtual vector<Contact*> operator()() override;

		void setTarget(const string& newTarget) {  }
	};
}

#endif