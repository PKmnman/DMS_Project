// Filename: DMS.cpp
// Author: Gary Reeves
// Date: 21/04/2021
// Compiler Used: MSVC

#include <algorithm>
#include <fstream>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>

#include "DMS.h"

using namespace std;
using namespace dms;


DMS::~DMS()
{
	for (auto query : queries)
	{
		delete query;
	}

	for (auto contact : contacts)
	{
		delete contact;
	}
}


DMS& DMS::getDMS()
{
	if (dms)
	{
		return *dms;
	}
	dms = new DMS();
	return *dms;
}


DMS* DMS::dms = nullptr;


void DMS::addContact(Contact& contact)
{
	contacts.push_back(&contact);
}


void DMS::removeContact(string& name)
{
	ranges::remove_if(contacts, [&name](Contact* ptr) -> bool
	{
		return ptr->getName() == name;
	});
}


void DMS::registerQuery(IQuery* const query_func)
{
	queries.push_back(query_func);
}


void DMS::addPersonalContact(std::string contact)
{
	const regex personal_capture = regex(
		R"(^([^,]+?),(.+?),(.+?),(.+?),(?:(?:"([^"]+?)["])|([^"]+?)),(.+?),(.+?),(\d+)$)");

	if (smatch match; regex_match(contact, match, personal_capture))
	{
		// Grab name and gender
		string name = match[NAME_FIELD];
		string gender = match[GENDER_FIELD];

		//Store contact using respective Contact classes
		contacts.push_back(new phone_pcontact(name, gender, match[PHONE_FIELD]));
		contacts.push_back(new email_contact(name, gender, match[EMAIL_FIELD]));
		contacts.push_back(new address_pcontact(
			name, gender, match[LADDRESS_FIELD].matched ? match[LADDRESS_FIELD] : match[SADDRESS_FIELD],
			match[DISTRICT_FIELD], match[STATE_FIELD], match[ZIPCODE_FIELD]
		));
	}
}


void DMS::addBusinessContact(std::string contact)
{
	// TODO: Process business conacts
}


void DMS::loadData(const string& filepath)
{
	// Open file
	ifstream file(filepath, ios::in);
	// Check file was opened properly
	if (!file.is_open())
	{
		throw exception("Unable to open file!!");
	}

	// Init variables
	string fileDesc;

	// Extract the first line parameters
	getline(file, fileDesc);
	const size_t comma_pos = fileDesc.find(',');

	const int nContacts = stoi(fileDesc.substr(0, comma_pos));
	const string contactType = fileDesc.substr(comma_pos + 1);


	if (contactType == "person")
	{
		string contact;

		while (file.good())
		{
			// Grab a line of input
			getline(file, contact);

			// Add a Personal Contact to the DMS
			addPersonalContact(contact);
		}
	}
	else if (contactType == "business")
	{
		string contact;
		while (file.good())
		{
			// Grab a line of input
			getline(file, contact);

			// Add a Business Contact to the DMS
			addBusinessContact(contact);
		}
	}
	else
	{
		throw exception("Unrecognized input format!!");
	}
}
