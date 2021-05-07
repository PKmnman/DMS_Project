#ifndef QUERY_H
#define QUERY_H

#include <map>
#include <queue>
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
	
	class SearchExpression
	{
	protected:
		// Stores the results of the expression
		vector<Contact*> results;
	
	public:

		SearchExpression()
		{
			results = {};
		}

		virtual ~SearchExpression();
		
		virtual Contact* operator[](size_t i) const
		{
			return results[i];
		};

		virtual size_t size() const { return results.size(); }
		
		virtual vector<Contact*> search(const vector<Contact*>& contacts) = 0;

		vector<Contact*> getResults() const { return results; }
		
	};

	
	class SearchResult : public SearchExpression
	{
		
	public:

		SearchResult() = default;
		
		SearchResult(const vector<Contact*>& list);

		SearchResult(SearchExpression const& expr);

		virtual Contact* operator[](size_t i) const { return results[i]; }

		virtual vector<Contact*> search(const vector<Contact*>& contacts)
		{
			// Don't do anything, just return the argument. This is a stub
			return contacts;
		}

		void operator=(const SearchResult& other);
		
	};

	enum Field : int { NAME, GENDER, PHONE_NUMBER, EMAIL, ADDRESS, STATE, ZIPCODE, CATEGORY, WEBSITE };

	// Class for grouping aggregate search expressions
	class GroupByCount
	{
		map<string, int> result;
		Field targetField;
		
	public:

		GroupByCount(int f) : targetField(static_cast<Field>(f)) {}
		
		map<string, int> operator()(vector<Contact*> list);
		
	};

	class NameSearch : public SearchExpression
	{
		// Name to search for
		string name;
		
	public:

		NameSearch(const string& name) : name(name) {}

		Contact* operator[](size_t i) const override
		{
			return results[i];
		}

		vector<contact_pt> search(const vector<Contact*>& contacts) override;
	};


	class GenderSearch : public SearchExpression
	{
		string gender;

	public:

		GenderSearch(const string& gender) : gender(gender) {}

		vector<contact_pt> search(const vector<Contact*>& contacts) override;
	};


	class PhoneSearch : public SearchExpression
	{
		string phone;

	public:

		PhoneSearch(const string& phoneNumber) : phone(phoneNumber) {}

		vector<contact_pt> search(const vector<Contact*>& contacts) override;
	};


	class EmailSearch : public SearchExpression
	{
		string email;

	public:

		EmailSearch(const string& address) : email(address) {}

		vector<contact_pt> search(const vector<Contact*>& contacts) override;
	};


	class StateSearch : public SearchExpression
	{
		string state;

	public:

		StateSearch(const string& state) : state(state) {}

		vector<contact_pt> search(const vector<Contact*>& contacts) override;
	};

	
	// Operators for handling search expressions

	SearchResult operator >>(vector<Contact*>&& contacts, SearchExpression& b);

	SearchResult operator >>(SearchExpression& a, SearchExpression& b);

	SearchResult operator >>(SearchResult&& a, SearchExpression& b);

	map<string, int> operator >>(SearchExpression& expr, GroupByCount group_by);
	
	// Search IQuery

	class SearchQuery : public IQuery
	{

		static vector<string> paramNames;

		string query;

	protected:

		SearchResult result;

	public:

		static map<string, int> generateParamNumMap();

		static vector<string> getParamNames() { return paramNames; }
		static bool isValidParamName(const string& param_name);

		SearchQuery(const string& search_query);

		void search();

		vector<Contact*> operator()() override;

		vector<Contact*> getResult() { return result.getResults(); }

	};

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

		void setTarget(const string& newTarget) { this->target = newTarget; }
	};
}
#endif
