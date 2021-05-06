#ifndef DMS_H
#define DMS_H

#include <map>
#include <vector>
#include <string>

#include "Contact.h"
#include "Query.h"
#include "Partition.h"

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
	
	
	class DMS
	{
		// Storage for contacts

		map<string, IQuery*> queries;

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
		
		// Function to register a query to the DMS
		void registerQuery(const string& key, IQuery* const query_func);

		template <typename T>
		T* getQuery(const string& name)
		{
			IQuery* query = queries.at(name);
			return static_cast<T*>(query);
		}


		void addPersonalContact(std::string contact);
		void addBusinessContact(std::string contact);
		
		// Function to load contact data from file
		void loadData(const string& filepath);

		const vector<Contact*> getContacts() const { return contacts; }
		friend class TimingWheel;
	};

	
	
}

#endif