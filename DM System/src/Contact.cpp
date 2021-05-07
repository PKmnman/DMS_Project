#include "Contact.h"
#include <iostream>
#include <regex>

namespace dms::contact
{

	bool operator==(const Contact& c, const string& name)
	{
		if (c.getName().size() == name.size())
		{
			for (size_t i = 0; i < name.size(); i++)
			{
				if (c.getName().at(i) != '*' && c.getName().at(i) != name.at(i)) return false;
			}

			return true;
		}

		return false;
	}

	bool operator==(const PhoneInfo& pn, const string& name)
	{
		if (name.size() != pn.getPhoneNumber().size()) return false;

		string number = pn.getPhoneNumber();
		for (size_t i = 0; i < name.size(); i++)
		{
			if (number.at(i) != '*' && number.at(i) != name.at(i)) return false;
		}

		return true;

	}
	
	PhoneInfo::PhoneInfo(CSZREF phone)
	{
		// Validate the number first
		if(smatch results; regex_match(phone, results, PHONE_EXPR))
		{
			// Store full phone number
			phone_number = results[0];

			// Store values of each section of the number
			country_code = stoi(results[1]);
			area_code = stoi(results[2]);
			exchange_code = stoi(results[3]);
			line_number = stoi(results[4]);
		}
		else
		{
			// Form error message
			const string err_msg = string("Invalid phone number: ") + phone;
			// Throw an exception
			throw exception(err_msg.c_str());
		}
	}

	
	bool PhoneInfo::setPhoneNumber(CSZREF phone)
	{
		// Validate the phone number
		if (smatch results; regex_match(phone, results, PHONE_EXPR))
		{
			// Store full phone number
			phone_number = results[0];

			// Store values of each section of the number
			country_code = stoi(results[1]);
			area_code = stoi(results[2]);
			exchange_code = stoi(results[3]);
			line_number = stoi(results[4]);

			return true;
		}
		
		return false;
	}

	EmailInfo::EmailInfo(CSZREF email)
	{
		if(smatch results; regex_match(email, results, EMAIL_EXPR))
		{
			address = email;
			domain = results[3];
			
		}
		else
		{
			throw exception("Invalid email!!!");
		}
	}

	
	void EmailInfo::setAddress(const string& email)
	{
		if (smatch results; regex_match(email, results, EMAIL_EXPR))
		{
			address = email;
			domain = results[3];
		}
	}

	bool operator==(const EmailInfo& c, const string& name)
	{
		if (c.getAddress().size() == name.size())
		{
			for (size_t i = 0; i < name.size(); i++)
			{
				if (c.getAddress().at(i) != '*' && c.getAddress().at(i) != name.at(i)) return false;
			}

			return true;
		}

		return false;
	}


	void PersonEmailContact::display()
	{
		cout << "[" << typeid(*this).name() << "]\t" <<
			"Name: " << Contact::name << "  |  " <<
			"Gender: " << gender << "  |  " <<
			"Email: " << address << endl;
	}


	void PersonPhoneContact::display()
	{
		cout << "[" << typeid(*this).name() << "]\t" <<
			"Name: " << Contact::name << "  |  " <<
			"Gender: " << gender << "  |  " <<
			"Phone: " << phone_number << endl;
	}


	void PersonAddressContact::display()
	{
		cout << "[" << typeid(*this).name() << "]\t" <<
			"Name: " << Contact::name << "  |  " <<
			"Gender: " << gender << "  |  " <<
			"Address: " << street_address << "  |  " <<
			"District: " << district << "  |  " <<
			"State: " << state << "  |  " <<
			"Zipcode: " << zipcode << endl;
	}


	void BusinessWebContact::display()
	{
		cout << "[" << typeid(*this).name() << "]\t" <<
			"Name: " << Contact::name << "  |  " <<
			"Category: " << category << "  |  " <<
			"Website: " << website << endl;
	}


	void BusinessPhoneContact::display()
	{
		cout << "[" << typeid(*this).name() << "]\t" <<
			"Name: " << Contact::name << "  |  " <<
			"Category: " << category << "  |  " <<
			"Phone: " << phone_number << endl;
	}


	void BusinessAddressContact::display()
	{
		cout << "[" << typeid(*this).name() << "]\t" <<
			"Name: " << Contact::name << "  |  " <<
			"Category: " << category << "  |  " <<
			"Address: " << street_address << "  |  " <<
			"District: " << district << "  |  " <<
			"State: " << state << "  |  " <<
			"Zipcode: " << zipcode << endl;
	}


	ostream& operator<<(ostream& out, const Contact& c)
	{
		return out << c.getName();
	}

	ostream& operator<<(ostream& out, const PersonContact& c)
	{
		return out << static_cast<Contact const&>(c) << ", " << c.getGender();
	}

	ostream& operator<<(ostream& out, const BusinessContact& c)
	{
		return out;
	}

	ostream& operator<<(ostream& out, const EmailInfo& i)
	{
		return out;
	}

	ostream& operator<<(ostream& out, const PhoneInfo& i)
	{
		return out;
	}

	ostream& operator<<(ostream& out, const WebInfo& i)
	{
		return out;
	}
}


