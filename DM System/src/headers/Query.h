#pragma once
#include <functional>
#include <vector>
#include "Contact.h"

using namespace std;

namespace dms
{
	class Query
	{
	public:

		vector<Contact*> operator ()(const char* t);

	};
}
