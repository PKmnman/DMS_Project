#pragma once
#include <string>

namespace dms
{
	using namespace std;

	constexpr int BYTE_MASK_3 = 0x00000FFF;
	constexpr int BYTE_MASK_4 = 0x0000FFFF;

	constexpr int APPLY_MASK(int VALUE, int SHIFT, unsigned int MASK){
		return (VALUE >> SHIFT) & MASK;
	}


	constexpr char digitVal(unsigned char ascii) {
		return ascii - 48;
	}


	struct PhoneNumberValueError : public exception
	{
		PhoneNumberValueError(const string& msg) : exception(msg.c_str()) {}
	};


	struct PhoneNumberLengthError : exception
	{
		PhoneNumberLengthError(int num_length) : exception() 
		{
			
		}
	};


	class phone_num
	{
		unsigned long areaCode : 12;
		unsigned long coeCode : 12;
		unsigned long lineNumber : 16;

	public:

		phone_num() : areaCode(0), coeCode(0), lineNumber(0) {}
		phone_num(const string& number);
		phone_num(const phone_num& other);

		int getAreaCode() const;

		int get(unsigned int index) const;

		void operator =(const phone_num& other);
		bool operator ==(const phone_num& other);

		int operator [](unsigned int index);

		operator string();
		operator const char*();

		friend phone_num operator "" _pn(const char*);

	};

	phone_num operator "" _pn(const char*);

}