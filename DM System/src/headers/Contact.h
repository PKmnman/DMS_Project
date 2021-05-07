#ifndef DMSCONTACT_H
#define DMSCONTACT_H
#include <string>
#include <regex>

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

			virtual ~Contact() = default;

			virtual void display() = 0;

			const string& getName() const { return name; }
			void setName(CSZREF newName) { name = newName; }
		};


		bool operator==(const Contact& c, const string& name);
		

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

			const string& getCategory() const { return category; }
			void setCategory(CSZREF new_category) { category = new_category; }

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

			CSZREF getGender() const { return gender; }
			void setGender(CSZREF value) { gender = value; }

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

			virtual ~AddressInfo() = default;
			
			virtual void display() = 0;

			const string& getStreetAddress() const
			{
				return street_address;
			}

			const string& getDistrict() const
			{
				return district;
			}

			const string& getState() const
			{
				return state;
			}

			const string& getZipcode() const
			{
				return zipcode;
			}
		};
		
		class PhoneInfo
		{
		protected:

			string phone_number;

			// More specific fields for queries
			
			int country_code;
			int area_code;
			int exchange_code;
			int line_number;

		public:

			PhoneInfo(CSZREF phone);
			PhoneInfo() : PhoneInfo("1-200-200-0000") {}

			virtual ~PhoneInfo() = default;
			
			virtual void display() = 0;

			int getCountryCode() const { return country_code; }

			int getAreaCode() const { return area_code; }

			int getExchangeCode() const { return exchange_code; }

			int getLineNumber() const { return line_number; }

			bool setPhoneNumber(CSZREF phone);

			string getPhoneNumber() const { return phone_number; }
		};

		
		bool operator==(const PhoneInfo& c, const string& name);

		class EmailInfo
		{
		protected:

			string address;

			string domain;

		public:

			EmailInfo(CSZREF email);
			EmailInfo() : EmailInfo("none@mail.com") {}

			virtual ~EmailInfo() = default;

			virtual void display() = 0;

			const string& getAddress() const { return address; }

			void setAddress(const string& email);

		};

		const regex PHONE_EXPR = regex(R"(^(\d{1,3})-(\d{3})-(\d{3})-(\d{4})$)");
		const regex EMAIL_EXPR = regex(R"((\w+(?:[.-_]\w+)?)@(\w+((?:.\w+)+)))");
		
		bool operator==(const EmailInfo& c, const string& name);
		

		class WebInfo
		{
		protected:
	
			string website;

		public:

			WebInfo(CSZREF url) : website(url) {}

			WebInfo() : WebInfo("none") {}

			virtual void display() = 0;

			const string& getWebAddress() const { return website; }
			
		};


		class PersonEmailContact : public PersonContact, public EmailInfo
		{
		public:

			PersonEmailContact(CSZREF fullname, CSZREF gender, CSZREF email)
			{
				this->name = fullname;
				this->gender = gender;
				this->address = email;
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

			void display() override;

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

			void display() override;

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

			void display() override;

			BusinessAddressContact() : BusinessAddressContact("none", "none", "none", "none", "none", "none") {}
		};

		typedef Contact contact_t, *contact_pt;

		typedef PersonPhoneContact phone_pcontact;
		typedef BusinessPhoneContact phone_bcontact;
		
		typedef PersonAddressContact address_pcontact;
		typedef BusinessAddressContact address_bcontact;

		typedef PersonEmailContact email_contact;
		typedef BusinessWebContact web_contact;


		ostream& operator<<(ostream& out, const Contact& c);
		ostream& operator<<(ostream& out, const PersonContact& c);
		ostream& operator<<(ostream& out, const BusinessContact& c);
		ostream& operator<<(ostream& out, const EmailInfo& i);
		ostream& operator<<(ostream& out, const PhoneInfo& i);
		ostream& operator<<(ostream& out, const WebInfo& i);
	}
}

namespace contact = dms::contact;
#endif