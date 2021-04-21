#pragma once
#include <string>

namespace dms 
{
	using namespace std;

	typedef const string& CSZREF;

	namespace contact
	{
		class Contact
		{
		protected:

			string name;

		public:
	
			Contact(CSZREF fullname) : name(fullname) {}
			Contact() : Contact("none") {}

			virtual void display() = 0;

			const string& getName() { return name; }
			void setName(CSZREF newName) { name = newName; }
		};


		class BusinessContact : virtual public Contact
		{
		protected:

			string category;

		public:

			BusinessContact(CSZREF fullname, CSZREF category) : Contact(fullname)
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

			PersonContact(CSZREF fullname, CSZREF gender) : Contact(fullname)
			{
				this->gender = gender;
			}

			PersonContact(CSZREF gender) : gender(gender) {}

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
	
			AddressInfo(CSZREF name, CSZREF street_address, CSZREF district, CSZREF state, CSZREF zipcode)
			{
				this->street_address = street_address;
				this->district = district;
				this->state = state;
				this->zipcode = zipcode;
			}

			AddressInfo(CSZREF street, CSZREF district, CSZREF state, CSZREF zipcode) 
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

			PhoneInfo(CSZREF fullname, CSZREF phone) : phone_number(phone) {}

			PhoneInfo(CSZREF phone) : phone_number(phone) {}

			PhoneInfo() : PhoneInfo("none", "000-000-0000") {}

			virtual void display() = 0;

		};


		class EmailInfo
		{
		protected:

			string email;

		public:

			EmailInfo(CSZREF fullname, CSZREF email) : email(email) {}

			EmailInfo() : EmailInfo("none", "none") {}

			virtual void display() = 0;

		};


		class WebInfo
		{
		protected:
	
			string website;

		public:

			WebInfo(CSZREF fullname, CSZREF url) : website(url) {}

			WebInfo() : WebInfo("none", "none") {}

			virtual void display() = 0;

		};


		class PersonEmailContact : public PersonContact, public EmailInfo
		{
		public:

			PersonEmailContact(CSZREF fullname, CSZREF gender, CSZREF email)
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
	
			PersonPhoneContact(CSZREF fullname, CSZREF gender, CSZREF phone) : PersonContact(gender), PhoneInfo(phone), Contact(fullname) {}

			virtual void display();

			PersonPhoneContact() : PersonPhoneContact("none", "none", "none"){}
		};



		class PersonAddressContact : public PersonContact, public AddressInfo
		{
		public:

			PersonAddressContact(CSZREF fullname, CSZREF gender, CSZREF street_address, CSZREF district, CSZREF state, CSZREF zipcode)
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
	
			BusinessWebContact(CSZREF fullname, CSZREF category, CSZREF url)
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

			BusinessPhoneContact(CSZREF name, CSZREF category, CSZREF phone)
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

			BusinessAddressContact(CSZREF fullname, CSZREF category, CSZREF street_address, CSZREF district, CSZREF state, CSZREF zipcode)
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
}

namespace contact = dms::contact;