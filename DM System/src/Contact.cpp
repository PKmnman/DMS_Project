#include "Contact.h"
#include <iostream>
#include <regex>

namespace dms::contact
{
	
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

}


