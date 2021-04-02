#include "Contact.h"

int main()
{
	Contact* test = new BusinessWebContact("Gary Inc.", "Web Development", "www.pkstudios.com");
	test->display();

	Contact* phoneperson = new PersonPhoneContact("Gary Reeves", "Non-Binary", "12037367606");
	phoneperson->display();
}