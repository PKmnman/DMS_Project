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
		for (int i = 0; const auto key : paramNames)
		{
			result[key] = i;
			i++;
		}
		return result;
	}
	

	// Checks whether or not 
	bool SearchQuery::isValidParamName(const string& param_name)
	{
		for(const auto& name : paramNames)
		{
			if(param_name == name) return true;
		}
		return false;
	}

	vector<string> SearchQuery::paramNames = { "name", "gender", "phone", "email", "address", "state", "zipcode", "orderby" };

	// Constructs a search query from a parameterized query string
	SearchQuery::SearchQuery(const string& search_query)
	{
		query = search_query;
		result = DMS::getDMS().getContacts();
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
		{
			try {
				if (isValidParamName(mr[1].str()))
				{
					// Check that we haven't already set this parameter
					if (tracker[mr[1].str()]) throw exception("Search parameter set multiple times!!!");
					tracker[mr[1].str()] = true;
					// Push parameter:value pair into the list of tokens
					parameters.emplace_back(string(mr[1]), string(mr[2]));

					temp = mr.suffix();
				}
				else
				{
					throw exception("Invalid parameter token!!!");
				}
			}
			catch (exception& e)
			{
				cerr << e.what();
			}

		}

		// Check that we received valid parameters
		if (parameters.empty()) throw exception("Invalid search string!!!");
		
		for (const auto& param : parameters)
		{
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
					// TODO: add
					break;
				case ZIPCODE:
					break;
				default:
					throw exception("Invalid param type!!");
				}
			}catch (out_of_range& e)
			{
				continue;
			}
		}
	}

	
	vector<Contact*> SearchQuery::operator()()
	{
		search();
		return result.getResults();
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


	SearchResult::SearchResult(const vector<Contact*>& list)
	{
		results= vector<Contact*>(list.size());
		for(int i = 0; i < list.size(); i++)
		{
			results[i] = list[i];
		}
	}

	
	SearchResult::SearchResult(SearchExpression const& expr)
	{
		results = vector<Contact*>(expr.size());
		for (size_t i = 0; i != expr.size(); i++) results[i] = expr[i];
	}

	
	void SearchResult::operator=(const SearchResult& other)
	{
		this->results = vector<Contact*>(other.getResults().size());

		for(int i = 0; i < other.size(); i++)
		{
			results[i] = other[i];
		}
	}
	

	vector<contact_pt> NameSearch::search(const vector<Contact*>& contacts)
	{
		for (auto c : contacts)
		{
			if (c->getName() == name) results.push_back(c);
		}
		return results;
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

		return results;
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
			if (typeid(*c) == typeid(AddressInfo) && dynamic_cast<AddressInfo*>(c)->getState() == state) results.push_back(c);
		}

		return results;
	}

	
	SearchResult operator>>(vector<Contact*>&& contacts, SearchExpression& b) { return b.search(contacts); }

	SearchResult operator>>(SearchExpression& a, SearchExpression& b) { return SearchResult(a.getResults() >> b); }

	SearchExpression::~SearchExpression()
	{
		for(int i = 0; i < results.size(); i++) results[i] = nullptr;
	}

}