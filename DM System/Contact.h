#pragma once
#include <string>

using namespace std;

#define STRING_REF const string&

class Contact
{
protected:

	string name;

public:
	
	Contact(STRING_REF fullname) : name(fullname) {}
	Contact() : Contact("none") {}

	virtual void display() = 0;

	const string& getName() { return name; }
	void setName(STRING_REF newName) { name = newName; }
};


class BusinessContact : virtual public Contact
{
protected:

	string category;

public:

	BusinessContact(STRING_REF fullname, STRING_REF category) : Contact(fullname)
	{
		this->category = category;
	}

	BusinessContact() : BusinessContact("none", "none") {}
	
	virtual void display() = 0;

	const string& getCategory() { return category; }

};


class PersonContact : virtual public Contact
{
protected:

	string gender;

public:

	PersonContact(STRING_REF fullname, STRING_REF gender) : Contact(fullname)
	{
		this->gender = gender;
	}

	PersonContact(STRING_REF gender) : gender(gender) {}

	PersonContact() : PersonContact("none", "none") {}

	virtual void display() = 0;

};


class AddressContact : virtual public Contact
{
protected:

	string street_address;
	string district;
	string state;
	string zipcode;

public:
	
	AddressContact(STRING_REF name, STRING_REF street_address, STRING_REF district, STRING_REF state, STRING_REF zipcode) : Contact(name)
	{
		this->street_address = street_address;
		this->district = district;
		this->state = state;
		this->zipcode = zipcode;
	}

	AddressContact(STRING_REF street, STRING_REF district, STRING_REF state, STRING_REF zipcode) 
	{
		this->street_address = street;
		this->district = district;
		this->state = state;
		this->zipcode = zipcode;
	}
	
	AddressContact() : AddressContact("none","none","none","none","none") {}
	
	virtual void display() = 0;

};


class PhoneContact : virtual public Contact
{
protected:

	string phone_number;

public:

	PhoneContact(STRING_REF fullname, STRING_REF phone) : Contact(fullname), phone_number(phone) {}

	PhoneContact(STRING_REF phone) : phone_number(phone) {}

	PhoneContact() : PhoneContact("none", "000-000-0000") {}

	virtual void display() = 0;

};


class EmailContact : virtual public Contact
{
protected:

	string email;

public:

	EmailContact(STRING_REF fullname, STRING_REF email) : Contact(fullname), email(email) {}

	EmailContact() : EmailContact("none", "none") {}

	virtual void display() = 0;

};


class WebContact : virtual public Contact
{
protected:
	
	string website;

public:

	WebContact(STRING_REF fullname, STRING_REF url) : Contact(fullname),  website(url) {}

	WebContact() : WebContact("none", "none") {}

	virtual void display() = 0;

};


class PersonEmailContact : public PersonContact, public EmailContact
{
public:

	PersonEmailContact(STRING_REF fullname, STRING_REF gender, STRING_REF email)
	{
		this->name = fullname;
		this->gender = gender;
		this->email = email;
	}

	virtual void display();

	PersonEmailContact() : PersonEmailContact("none", "none", "none") {}
};


class PersonPhoneContact : public PersonContact, public PhoneContact
{
public:
	
	PersonPhoneContact(STRING_REF fullname, STRING_REF gender, STRING_REF phone) : PersonContact(gender), PhoneContact(phone), Contact(fullname) {}

	virtual void display();

	PersonPhoneContact() : PersonPhoneContact("none", "none", "none"){}
};



class PersonAddressContact : public PersonContact, public AddressContact
{
public:

	PersonAddressContact(STRING_REF fullname, STRING_REF gender, STRING_REF street_address, STRING_REF district, STRING_REF state, STRING_REF zipcode)
	{
		this->name = fullname;
		this->gender = gender;
		this->street_address = street_address;
		this->district = district;
		this->state = state;
		this->zipcode = zipcode;
	}

	virtual void display();

	PersonAddressContact() : PersonAddressContact("none", "none", "none", "none", "none", "none") {}
};


class BusinessWebContact : public BusinessContact, public WebContact
{
public:
	
	BusinessWebContact(STRING_REF fullname, STRING_REF category, STRING_REF url)
	{
		this->name = fullname;
		this->category = category;
		this->website = url;
	}

	virtual void display();

	BusinessWebContact() : BusinessWebContact("none", "none", "none") {}
};


class BusinessPhoneContact : public BusinessContact, public PhoneContact
{
public:

	BusinessPhoneContact(STRING_REF name, STRING_REF category, STRING_REF phone)
	{
		this->name = name;
		this->category = category;
		this->phone_number = phone;
	}

	virtual void display();
	
	BusinessPhoneContact() : BusinessPhoneContact("none","none","none"){}
};


class BusinessAddressContact : public BusinessContact, public AddressContact
{
public:

	BusinessAddressContact(STRING_REF fullname, STRING_REF category, STRING_REF street_address, STRING_REF district, STRING_REF state, STRING_REF zipcode)
	{
		this->name = fullname;
		this->category = category;
		this->street_address = street_address;
		this->district = district;
		this->state = state;
		this->zipcode = zipcode;
	}

	virtual void display();

	BusinessAddressContact() : BusinessAddressContact("none", "none", "none", "none", "none", "none") {}
};
