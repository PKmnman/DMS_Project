#include "Query.h"

#include <ranges>

#include "DMS.h"
#include "Contact.h"

namespace dms
{
	
	vector<Contact*> DisplayQuery::operator()()
	{
		for (auto contact : DMS::getDMS().getContacts())
		{
			// Search for a contact with a matching name
			if (contact->getName() == target)
			{
				// Display the first contact with a matching name
				contact->display();

				// return the displayed contact
				return { contact };
			}
		}
		
		// Yell that no contact was found and return a nullptr
		cout << "Contact not found!!" << endl;
		return { nullptr };
	}


	map<string, int> SearchQuery::generateParamNumMap()
	{
		map<string, int> result;
		for (int i = 1; const auto key : paramNames)
		{
			result[key] = i;
			i++;
		}
		return result;
	}

	
	bool SearchQuery::isValidParamName(const string& param_name)
	{
		for(const auto& name : paramNames)
		{
			if(param_name == name) return true;
		}
		return false;
	}


	// Constructs a search query from a parameterized query string
	SearchQuery::SearchQuery(const string& search_query)
	{
		smatch mr;
		vector<pair<string, string>> parameters;

		// Generate a bool map to track duplicate parameters
		auto tracker = getNewTokenTracker();

		// Generate a number map to help evaluate which search function to use
		map<string, int> paramMap = generateParamNumMap();
		
		// Perform a regex search until we've grabbed every parameter
		while(regex_search(search_query, mr, regex(R"(([^\s:,]*):([^:,]*))")))
		{
			if(isValidParamName(mr[1]))
			{
				// Check that we haven't already set this parameter
				if(tracker[mr[1]]) throw exception("Search parameter set multiple times!!!");
				
				// Push parameter:value pair into the list of tokens
				parameters.emplace_back(mr[0], mr[2]);
				tracker[mr[1]] = true;
			}
			else
			{
				throw exception("Invalid parameter token!!!");
			}
			
		}

		// Check that we received valid parameters
		if(parameters.empty()) throw exception("Invalid search string!!!");

		// Start with the entire DMS
		result = DMS::getDMS().getContacts();
			
		search(parameters);
		
	}

	void SearchQuery::search(const vector<pair<string, string>> parameters)
	{
		for (const auto& param : parameters)
		{
			// Apply the correct function based on the parameter name
			switch (paramMap.at(param.first))
			{
			case NAME:
				result >> *new NameSearch(param.second);
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
				break;
			case STATE:
				break;
			case ZIPCODE:
				break;
			default:
				throw exception("Invalid param type!!");
			}
		}
	}

	
	vector<Contact*> SearchQuery::operator()()
	{
		return vector<Contact*>();
	}

	map<string, bool> getNewTokenTracker()
	{
		map<string, bool> result;
		for (auto expr : SearchQuery::getParamNames())
		{
			result[expr] = false;
		}
		return result;
	}


	vector<contact_pt> GenderSearch::search(const vector<Contact*>& contacts)
	{
		for (auto c : contacts)
		{
			if (typeid(*c) == typeid(PersonContact) && dynamic_cast<PersonContact*>(c)->getGender() == gender)
			{
				results.push_back(c);
			}
		}
	}

	vector<contact_pt> PhoneSearch::search(const vector<Contact*>& contacts)
	{
		for (auto c : contacts)
		{
			if (typeid(*c) == typeid(PhoneInfo) && dynamic_cast<PhoneInfo*>(c)->getPhoneNumber() == phone)
			{
				results.push_back(c);
			}
		}

		return results;
	}

	vector<contact_pt> EmailSearch::search(const vector<Contact*>& contacts)
	{
		for (auto c : contacts)
		{
			if (typeid(*c) == typeid(EmailInfo) && *dynamic_cast<EmailInfo*>(c) == email) results.push_back(c);
		}

		return results;
	}


	vector<contact_pt> StateSearch::search(const vector<Contact*>& contacts)
	{
		for (auto c : contacts)
		{
			if (typeid(*c) == typeid(AddressInfo))
			{
				if(dynamic_cast<AddressInfo*>(c)->getState() == state) results.push_back(c);
			}
		}

		return results;
	}
	
	
	SearchExpression::~SearchExpression()
	{
		for(int i = 0; i < results.size(); i++)
		{
			results[i] = nullptr;
		}
	}

}