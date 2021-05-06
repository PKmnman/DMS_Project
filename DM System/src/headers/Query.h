#ifndef QUERY_H
#define QUERY_H

#include <map>
#include <string>
#include <vector>
#include <regex>

#include "Contact.h"

#define NAME_SEARCH 1
#define GENDER_SEARCH 2
#define PHONE_SEARCH 3
#define EMAIL_SEARCH 4
#define ADDRESS_SEARCH 5
#define STATE_SEARCH 6
#define ZIPCODE_SEARCH 7

using namespace std;

namespace dms
{
	using namespace contact;
	
	class IQuery
	{
	protected:
		
		IQuery() = default;

	public:

		virtual ~IQuery() = default;

		virtual vector<Contact*> operator ()() = 0;

	};


	// A lot of complicated stuff used to evaluate search queries
	
	template <typename E>
	class SearchExpression
	{
	protected:

		vector<Contact*> results;
	
	public:

		SearchExpression()
		{
			results = {};
		}
		
		Contact* operator[](size_t i) const { return static_cast<E const&>(*this)[i]; }

		size_t size() const
		{
			return static_cast<E const&>(*this).size();
		}
		
		vector<Contact*> search(const vector<Contact*>& contacts)
		{
			static_cast<E const&>(*this).search(contacts);
		}

		vector<Contact*> getResults() const { return results; }
		
	};

	
	class SearchResult : public SearchExpression<SearchResult>
	{
		
	public:

		SearchResult() = default;
		
		SearchResult(const vector<Contact*>& list) { results = list; }

		Contact* operator[](size_t i) const { return results[i]; }

		vector<Contact*> search(const vector<Contact*>& contacts)
		{
			// Don't do anything, just return the argument. This is a stub
			return contacts;
		}
		
		template <typename E>
		SearchResult(SearchExpression<E> const& expr)
		{
			results = vector<Contact*>(expr.size());
			
			for (size_t i = 0; i != expr.size(); i++)
			{
				results[i] = expr[i];
			}
		}
		
	};


	class NameSearch : public SearchExpression<NameSearch>
	{

		string name;
		
	public:

		NameSearch(const string& name) : name(name) {}

		Contact* operator[](size_t i) const
		{
			return results[i];
		}
		
		vector<contact_pt> search(const vector<Contact*>& contacts)
		{
			for(auto c : contacts)
			{
				if(c->getName() == name) results.push_back(c);
			}
		}
		
	};


	class GenderSearch : public SearchExpression<GenderSearch>
	{
		string gender;

	public:

		GenderSearch(const string& gender) : gender(gender) {}

		vector<contact_pt> search(const vector<Contact*>& contacts)
		{
			for (auto c : contacts)
			{
				if (typeid(*c) == typeid(PersonContact) && dynamic_cast<PersonContact*>(c)->getGender() == gender)
				{
					results.push_back(c);
				}
			}
		}
	};


	class PhoneSearch : public SearchExpression<PhoneSearch>
	{
		string phone;

	public:

		PhoneSearch(const string& phoneNumber) : phone(phoneNumber) {}

		vector<contact_pt> search(const vector<Contact*>& contacts)
		{
			for (auto c : contacts)
			{
				if (typeid(*c) == typeid(PhoneInfo) && dynamic_cast<PhoneInfo*>(c)->getPhoneNumber() == phone)
				{
					results.push_back(c);
				}
			}
		}
	};


	class EmailSearch : public SearchExpression<EmailSearch>
	{
		string email;

	public:

		EmailSearch(const string& address) : email(address) {}

		vector<contact_pt> search(const vector<Contact*>& contacts);
	};

	// Operators for handling search expressions
	
	template <typename T1, typename T2>
	SearchResult operator >>(const SearchExpression<T1>& a, const SearchExpression<T2>& b)
	{
		return SearchResult(a.results >> b);
	}

	
	template <typename T>
	SearchResult operator >>(SearchResult& a, const SearchExpression<T>& b)
	{
		a = SearchResult(a.getResults() >> b);
		return a;
	}

	
	template <typename T>
	SearchResult operator >>(const vector<Contact*>& contacts, const SearchExpression<T>& b)
	{
		return b.search(contacts);
	}

	// Search IQuery

	class SearchQuery : public IQuery
	{
		static const map<string, int> paramMap;

		static vector<string> paramNames;

		string query;

	protected:

		SearchResult result;
		
		SearchResult search(const vector<pair<string, string>> parameters);

	public:

		static int getParamNum(const string& paramName);
		static map<string, int> generateParamNumMap();

		static vector<string> getParamNames() { return paramNames; }
		static bool isValidParamName(const string& param_name);

		SearchQuery(const string& search_query);

		vector<Contact*> operator()() override;
		void clearResult();

	};

	vector<string> SearchQuery::paramNames = { "name", "gender", "phone", "email", "address", "state", "zipcode" };

	map<string, bool> getNewTokenTracker();

	// Display IQuery
	
	class DisplayQuery : public IQuery
	{
		string target;
	public:

		DisplayQuery() : IQuery() {}

		DisplayQuery(const string& target)
		{
			this->target = target;
		}

		virtual vector<Contact*> operator()();

		void setTarget(const string& newTarget) {  }
	};
}
#endif
