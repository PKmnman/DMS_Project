#include "DMS.h"
#include <algorithm>

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
}
