#include "DMS.h"
#include <fstream>
#include <algorithm>
#include <string>

void dms::DMS::addContact(Contact& contact)
{
	contacts.push_back(&contact);
}

void dms::DMS::removeContact(string& name)
{
	ranges::remove_if(contacts, [&name](Contact* ptr) -> bool
	{
		return ptr->getName() == name;
	});
}

std::map<std::string&, int> dms::DMS::search()
{
	// TODO: Implement search query
}

void dms::DMS::registerQuery(string& key, Query* const query_func)
{
	queries.insert_or_assign(key, query_func);
}

void dms::DMS::loadData(const string& filepath)
{
	// TODO: Populate the DMS
	vector <string> tokenizedfile;
	int size;	
	string first;
	string type;
	ifstream file;
	file.open(filepath, ios::in);
	getline(file, first, ',');
	size = stoi(first.substr(0, first.find(",") + 1));
	type = first.substr(first.rfind(",") + 1);
	contacts.resize(size);
	
	if (type == "person") {
		if (file.is_open()) {
			string person;
			while (getline(file, person,' ')) {
				tokenizedfile.push_back(person);
				Contact* new_phone = &PersonPhoneContact(tokenizedfile[0], tokenizedfile[1], tokenizedfile[2]);
				Contact* new_email = &PersonEmailContact(tokenizedfile[0], tokenizedfile[1], tokenizedfile[3]);
				Contact* new_address = &PersonAddressContact(tokenizedfile[0], tokenizedfile[1], tokenizedfile[4], tokenizedfile[5], tokenizedfile[6], tokenizedfile[7]);
				contacts.push_back(new_phone);
				contacts.push_back(new_email);
				contacts.push_back(new_address);
			}
		}

	}
	else if("business"){
		//TODO: business contact generation using input file 2
	}
	else {
		throw uncaught_exceptions;
	}
}
