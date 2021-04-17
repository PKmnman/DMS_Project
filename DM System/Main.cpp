#include "Contact.h"
#include <fstream>

int main()
{
	Contact* test = new BusinessWebContact("Gary Inc.", "Web Development", "www.pkstudios.com");
	test->display();

	Contact* phoneperson = new PersonPhoneContact("Gary Reeves", "Non-Binary", "12037367606");
	phoneperson->display();

	Contact* dir[6];

	dir[0] = new PersonAddressContact();
	dir[1] = new PersonPhoneContact();
	dir[2] = new PersonEmailContact();
	dir[3] = new BusinessAddressContact();
	dir[4] = new BusinessPhoneContact();
	dir[5] = new BusinessWebContact();

	for (int i = 0; i < 6; i++)
	{

		dir[i]->display();

	}
}