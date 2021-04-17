#include "phone_num.h"

using namespace dms;

phone_num::phone_num(const string& number)
{
	if(number.size() != 10) throw PhoneNumberValueError("Invlaid phone number length!!");

	int char_digits[10];

	for (int i = 0; i < 10; i++)
	{
		if(number[i] < 48 || number[i] > 57) throw exception("Invlaid digit!!");

		char_digits[i] = digitVal(number[i]);
	}

	areaCode = (char_digits[0] << 8) & (char_digits[1] << 4) & char_digits[2];
	coeCode = (char_digits[3] << 8) & (char_digits[4] << 4) & char_digits[5];
	lineNumber = (char_digits[6] << 12) & (char_digits[7] << 8) & (char_digits[8] << 4) & char_digits[9];
}


phone_num dms::operator"" _pn(const char* lit)
{
	int len = strlen(lit);
	
	if(len != 10) throw PhoneNumberValueError("Invlaid phone number length!!");

	int char_digits[10];

	for (int i = 0; i < 10; i++)
	{
		if (lit[i] < 48 || lit[i] > 57) throw exception("Invlaid digit!!");

		char_digits[i] = digitVal(lit[i]);
	}

	phone_num num;

	num.areaCode = (lit[0] << 8) & (lit[1] << 4) & lit[2];
	num.coeCode = (lit[3] << 8) & (lit[4] << 4) & lit[5];
	num.lineNumber = (lit[6] << 12) & (lit[7] << 8) & (lit[8] << 4) & lit[9];


	return phone_num();
}
