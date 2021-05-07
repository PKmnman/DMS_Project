#include "pch.h"
#include "Contact.h"
#include "CppUnitTest.h"
#include "Query.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dms;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			vector<Contact*> contacts {
				new PersonPhoneContact("Gary Reeves", "Non-Binary", "2037777777")
			};

			SearchResult r = contacts;

			r >> NameSearch("Gary Reeves");

			Assert::AreEqual((int)contacts[0], (int)r[0]);
		}
	};
}
