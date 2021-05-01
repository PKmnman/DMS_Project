#include "DMS.h"
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <regex>

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


void dms::DMS::addPersonalContact(std::string contact)
{
	const regex personal_capture = regex(R"(^([^,]+?),(.+?),(.+?),(.+?),(?:(?:"([^"]+?)["])|([^"]+?)),(.+?),(.+?),(\d+)$)");
			
	if(smatch match; regex_match(contact, match, personal_capture))
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


void dms::DMS::loadData(const string& filepath)
{
	// Open file
	ifstream file(filepath, ios::in);
	// Check file was opened properly
	if(!file.is_open())
	{
		throw exception("Unable to open file!!");
	}

	// Init variables
	string fileDesc;
	
	// Extract the first line parameters
	getline(file, fileDesc);
	const size_t comma_pos = fileDesc.find(',');
	
	const int nContacts = stoi(fileDesc.substr(0,  comma_pos));
	const string contactType = fileDesc.substr(comma_pos + 1);
	
	
	if (contactType == "person") {
		string contact;

		while (file.good()) {
			// Grab a line of input
			getline(file, contact);

			// Add a Personal Contact to the DMS
			addPersonalContact(contact);
		}
	}
	else if (contactType == "business") {
		string contact;
		while (file.good()) {
			// Grab a line of input
			getline(file, contact);

			// Add a Personal Contact to the DMS
			addBusinessContact(contact);
		}
	}
	else{
		throw exception("Unrecognized input format!!");
	

	}

}
