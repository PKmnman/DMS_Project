#include "Contact.h"
#include <iostream>


void PersonPhoneContact::display()
{
	cout << "[" << typeid(*this).name() << "]\t" <<
		"Name: " << Contact::name << "  |  " <<
		"Gender: " << gender << "  |  " <<
		"Phone: " << phone_number << endl;
}


void BusinessWebContact::display()
{
	cout << "[" << typeid(*this).name() << "]\t" <<
	"Name: " << Contact::name << "  |  " <<
	"Category: " << category << "  |  " << 
	"Website: " << website << endl;
}


