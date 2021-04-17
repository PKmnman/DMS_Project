#include "Contact.h"
#include <iostream>


namespace dms
{

	void PersonEmailContact::display()
	{
		cout << "[" << typeid(*this).name() << "]\t" <<
			"Name: " << Contact::name << "  |  " <<
			"Gender: " << gender << "  |  " <<
			"Email: " << email << endl;
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


