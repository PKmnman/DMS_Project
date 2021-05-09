// Filename: Contact.cpp
// Author: Gary Reeves
// Date: 01/04/2021
// Compiler Used: MSVC

#include "Contact.h"

#include <iomanip>
#include <iostream>
#include <regex>

namespace dms
{
	namespace contact
	{
		


		PhoneInfo::PhoneInfo(CSZREF phone)
		{
			// Validate the number first
			if (smatch results; regex_match(phone, results, PHONE_EXPR))
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
			if (smatch results; regex_match(email, results, EMAIL_EXPR))
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
				"Name: " << name << "  |  " <<
				"Gender: " << gender << "  |  " <<
				"Email: " << address << endl;
		}


		void PersonPhoneContact::display()
		{
			cout << "[" << typeid(*this).name() << "]\t" <<
				"Name: " << name << "  |  " <<
				"Gender: " << gender << "  |  " <<
				"Phone: " << phone_number << endl;
		}


		void PersonAddressContact::display()
		{
			cout << "[" << typeid(*this).name() << "]\t" <<
				"Name: " << name << "  |  " <<
				"Gender: " << gender << "  |  " <<
				"Address: " << street_address << "  |  " <<
				"District: " << district << "  |  " <<
				"State: " << state << "  |  " <<
				"Zipcode: " << zipcode << endl;
		}


		void BusinessWebContact::display()
		{
			cout << "[" << typeid(*this).name() << "]\t" <<
				"Name: " << name << "  |  " <<
				"Category: " << category << "  |  " <<
				"Website: " << website << endl;
		}


		void BusinessPhoneContact::display()
		{
			cout << "[" << typeid(*this).name() << "]\t" <<
				"Name: " << name << "  |  " <<
				"Category: " << category << "  |  " <<
				"Phone: " << phone_number << endl;
		}


		void BusinessAddressContact::display()
		{
			cout << "[" << typeid(*this).name() << "]\t" <<
				"Name: " << name << "  |  " <<
				"Category: " << category << "  |  " <<
				"Address: " << street_address << "  |  " <<
				"District: " << district << "  |  " <<
				"State: " << state << "  |  " <<
				"Zipcode: " << zipcode << endl;
		}

		// Compares a EmailInfo object to a string. Supports wildcard characters
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

		// Compares a Contact to a string. Supports wildcard characters
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

		// Compares a PhoneInfo object to a string. Supports wildcard characters
		bool operator==(const PhoneInfo& pn, const string& other)
		{
			if (other.size() != pn.getPhoneNumber().size()) return false;

			string number = pn.getPhoneNumber();
			for (size_t i = 0; i < other.size(); i++)
			{
				if (number.at(i) != '*' && number.at(i) != other.at(i)) return false;
			}

			return true;
		}

		// Stream Insertion operators
		
		ostream& operator<<(ostream& out, const Contact& c)
		{
			return out << setw(12) << right
				<< "Name: " <<c.getName();
		}


		ostream& operator<<(ostream& out, const PersonContact& c)
		{
			return out << setw(12) << left
				<< "Name: " << c.getName() << endl
				<< setw(12) << left
				<< "Gender: " << c.getGender();
		}


		ostream& operator<<(ostream& out, const BusinessContact& c)
		{
			return out << setw(12) << left
				<< "Name: " << c.getName() << endl
				<< setw(12) << left
				<< "Category: " << c.getCategory();
		}


		ostream& operator<<(ostream& out, const AddressInfo& i)
		{
			return out << setw(12) << left
				<< "Address: " << i.getStreetAddress() << '\n'
				<< setw(12) << left << ' ' << i.getDistrict() << ", "
				<< i.getState() << ' ' << i.getZipcode();
		}


		ostream& operator<<(ostream& out, const EmailInfo& i)
		{
			return out << setw(12) << left
				<< "Email: " << i.getAddress();
		}


		ostream& operator<<(ostream& out, const PhoneInfo& i)
		{
			return out << setw(12) << left
				<< "Phone: " << i.getPhoneNumber();
		}


		ostream& operator<<(ostream& out, const WebInfo& i)
		{
			return out << setw(12) << left
				<< "Website: " << i.getWebAddress();
		}
	}
}
