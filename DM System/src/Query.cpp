// Filename: Query.cpp
// Author: Gary Reeves
// Date: 05/05/2021
// Compiler Used: MSVC

#include "Query.h"

#include <iomanip>
#include <iostream>
#include <ranges>

#include "Contact.h"
#include "DMS.h"

namespace dms
{
	map<string, int> SearchQuery::generateParamNumMap()
	{
		map<string, int> result;
		for (int i = 0; const auto key : paramNames)
		{
			result[key] = i;
			i++;
		}
		return result;
	}

	// Names of the search parameters
	vector<string> SearchQuery::paramNames = {
		"name", "gender", "phone", "email", "address", "state", "zipcode", "orderby"
	}; 


	// Constructs a search query from a parameterized query string
	SearchQuery::SearchQuery(const string& search_query)
	{
		query = search_query;
		result = DMS::getDMS().getContacts();
	}


	SearchResult::SearchResult(const vector<Contact*>& list)
	{
		results = vector<Contact*>(list.size());
		for (int i = 0; i < list.size(); i++) results[i] = list[i];
	}


	SearchResult::SearchResult(const SearchExpression& expr)
	{
		results = vector<Contact*>(expr.size());
		for (size_t i = 0; i != expr.size(); i++) results[i] = expr[i];
	}

	// Checks whether or not a parameter name is valid
	bool SearchQuery::isValidParamName(const string& param_name)
	{
		return std::ranges::any_of(paramNames, [&param_name](const string& s) {return param_name == s; });
	}

	// Generates a map for tracking whether
	map<string, bool> getNewTokenTracker()
	{
		map<string, bool> result;
		for (auto expr : SearchQuery::getParamNames()) result[expr] = false;
		return result;
	}


	void SearchQuery::search()
	{
		smatch mr;
		vector<pair<string, string>> parameters;

		// Generate a bool map to track duplicate parameters
		auto tracker = getNewTokenTracker();

		// Generate a number map to help evaluate which search function to use
		map<string, int> paramMap = generateParamNumMap();
		string temp = query;
		// Perform a regex search until we've grabbed every parameter
		while (regex_search(temp, mr, regex(R"(([^\s:,]+):([^:,]+))")))
			try
			{
				if (isValidParamName(mr[1].str()))
				{
					// Check that we haven't already set this parameter
					if (tracker[mr[1].str()]) throw exception("Search parameter set multiple times!!!");
					tracker[mr[1].str()] = true;
					// Push parameter:value pair into the list of tokens
					parameters.emplace_back(string(mr[1]), string(mr[2]));

					temp = mr.suffix();
				}
				else throw exception("Invalid parameter token!!!");
			}
			catch (exception& e)
			{
				cerr << e.what();
			}

		// Check that we received valid parameters
		if (parameters.empty()) throw exception("Invalid search string!!!");

		for (const auto& param : parameters)
			try
			{
				// Apply the correct function based on the parameter name
				switch (paramMap.at(param.first))
				{
					case NAME:
						result = result >> *new NameSearch(param.second);
						break;
					case GENDER:
						result >> *new GenderSearch(param.second);
						break;
					case PHONE_NUMBER:
						result >> *new PhoneSearch(param.second);
						break;
					case EMAIL:
						result >> *new EmailSearch(param.second);
						break;
					case ADDRESS:
						// TODO: add AddressSearch
						break;
					case STATE:
						// TODO: add StateSearch
						break;
					case ZIPCODE:
						break;
					default:
						throw exception("Invalid param type!!");
				}
			}
			catch (out_of_range& e) { }
	}

	// Search functions

	vector<contact_pt> NameSearch::search(const vector<Contact*>& contacts)
	{
		for (auto c : contacts) if (c->getName() == name) results.push_back(c);
		return results;
	}


	vector<contact_pt> GenderSearch::search(const vector<Contact*>& contacts)
	{
		for (auto c : contacts) if (typeid(*c) == typeid(PersonContact) && dynamic_cast<PersonContact*>(c)->getGender()
			== gender) results.push_back(c);

		return results;
	}


	vector<contact_pt> PhoneSearch::search(const vector<Contact*>& contacts)
	{
		for (auto c : contacts) if (typeid(*c) == typeid(PhoneInfo) && dynamic_cast<PhoneInfo*>(c)->getPhoneNumber() ==
			phone) results.push_back(c);

		return results;
	}


	vector<contact_pt> EmailSearch::search(const vector<Contact*>& contacts)
	{
		for (auto c : contacts) if (typeid(*c) == typeid(EmailInfo) && *dynamic_cast<EmailInfo*>(c) == email) results.
			push_back(c);

		return results;
	}


	vector<contact_pt> StateSearch::search(const vector<Contact*>& contacts)
	{
		for (auto c : contacts)
			if (typeid(*c) == typeid(AddressInfo) && dynamic_cast<AddressInfo*>(c)->getState() == state)
			{
				results.
					push_back(c);
			}

		return results;
	}

	// Operator Overloads

	vector<Contact*> DisplayQuery::operator()()
	{
		vector<Contact*> matches{};


		for (Contact* contact : DMS::getDMS().getContacts())
			// Search for a contact with a matching name
			if (contact->getName() == target)
			{
				// Display the first contact with a matching name
				matches.push_back(contact);
			}

		if (matches.empty())
		{
			cout << "Contact not found..." << endl;
			return matches;
		}

		// Tracks if we've printed this level of the hierarchy
		map<string, bool> tracker{
			{"PersonContact", false}, {"BusinessContact", false}
		};

		// Buffer line for output
		cout << endl;

		// Loop doesn't account for multiple contacts with the same name
		for (Contact* c : matches)
		{
			// Checks type through pointer casting and
			if (const auto actual = dynamic_cast<PersonContact*>(c); !tracker["PersonContact"] && actual)
			{
				cout << *actual << endl;
				tracker["PersonContact"] = true;
			}

			if (const auto actual = dynamic_cast<BusinessContact*>(c); !tracker["BusinessContact"] && actual)
			{
				cout << *actual << endl;
				tracker["BusinessContact"] = true;
			}

			if (const auto actual = dynamic_cast<PhoneInfo*>(c)) cout << *actual << endl;

			if (const auto actual = dynamic_cast<AddressInfo*>(c)) cout << *actual << endl;

			if (const auto actual = dynamic_cast<EmailInfo*>(c)) cout << *actual << endl;;
		}

		return matches;
	}


	vector<Contact*> SearchQuery::operator()()
	{
		search();
		return result.getResults();
	}


	void SearchResult::operator=(const SearchResult& other)
	{
		this->results = vector<Contact*>(other.getResults().size());

		for (int i = 0; i < other.size(); i++) results[i] = other[i];
	}


	SearchResult operator>>(vector<Contact*>&& contacts, SearchExpression& b) { return b.search(contacts); }


	SearchResult operator>>(SearchExpression& a, SearchExpression& b) { return SearchResult(a.getResults() >> b); }


	SearchExpression::~SearchExpression()
	{
		for (int i = 0; i < results.size(); i++) results[i] = nullptr;
	}
}
