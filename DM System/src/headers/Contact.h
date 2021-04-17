#pragma once
#include <string>

namespace dms 
{
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


	class AddressInfo
	{
	protected:

		string street_address;
		string district;
		string state;
		string zipcode;

	public:
	
		AddressInfo(STRING_REF name, STRING_REF street_address, STRING_REF district, STRING_REF state, STRING_REF zipcode)
		{
			this->street_address = street_address;
			this->district = district;
			this->state = state;
			this->zipcode = zipcode;
		}

		AddressInfo(STRING_REF street, STRING_REF district, STRING_REF state, STRING_REF zipcode) 
		{
			this->street_address = street;
			this->district = district;
			this->state = state;
			this->zipcode = zipcode;
		}
	
		AddressInfo() : AddressInfo("none","none","none","none","none") {}
	
		virtual void display() = 0;

	};


	class PhoneInfo
	{
	protected:

		string phone_number;

	public:

		PhoneInfo(STRING_REF fullname, STRING_REF phone) : phone_number(phone) {}

		PhoneInfo(STRING_REF phone) : phone_number(phone) {}

		PhoneInfo() : PhoneInfo("none", "000-000-0000") {}

		virtual void display() = 0;

	};


	class EmailInfo
	{
	protected:

		string email;

	public:

		EmailInfo(STRING_REF fullname, STRING_REF email) : email(email) {}

		EmailInfo() : EmailInfo("none", "none") {}

		virtual void display() = 0;

	};


	class WebInfo
	{
	protected:
	
		string website;

	public:

		WebInfo(STRING_REF fullname, STRING_REF url) : website(url) {}

		WebInfo() : WebInfo("none", "none") {}

		virtual void display() = 0;

	};


	class PersonEmailContact : public PersonContact, public EmailInfo
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


	class PersonPhoneContact : public PersonContact, public PhoneInfo
	{
	public:
	
		PersonPhoneContact(STRING_REF fullname, STRING_REF gender, STRING_REF phone) : PersonContact(gender), PhoneInfo(phone), Contact(fullname) {}

		virtual void display();

		PersonPhoneContact() : PersonPhoneContact("none", "none", "none"){}
	};



	class PersonAddressContact : public PersonContact, public AddressInfo
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


	class BusinessWebContact : public BusinessContact, public WebInfo
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


	class BusinessPhoneContact : public BusinessContact, public PhoneInfo
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


	class BusinessAddressContact : public BusinessContact, public AddressInfo
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
}