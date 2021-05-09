// Filename: Menu.cpp
// Author: Gary Reeves
// Date: 16/04/2021
// Compiler Used: MSVC

#include "Menu.h"
#include <iomanip>
#include <ranges>
#include <sstream>
#include "DMS.h"
#include "Partition.h"

using namespace menu;
using namespace std;


string MissingOptionError::format_msg(const string& menu, const string& option)
{
	stringstream str = stringstream(stringstream::out);
	str << "Cannot find option \'" << option << "\' in Menu titled \""
		<< menu << "\"." << ends;

	return str.str();
}


string Menu::generateHeader() const
{
	if (menu_title.empty()) return "";

	ostringstream str;

	const size_t BORDER_WIDTH = (2 * (menu_title.size() + 3)) + (menu_title.size() / 4) + 1;

	str << setfill('*')
		<< setw(BORDER_WIDTH) << right
		<< "\n"
		<< "   " << menu_title << endl
		<< setw(BORDER_WIDTH) << right
		<< "\n"
		<< ends;

	return str.str();
}


Menu::Menu(const string& title, const string& description)
{
	menu_title = title;
	menu_desc = description;
	isRunning = false;

	header_block = generateHeader();
}


void Menu::select(const string& option)
{
	if (options.contains(option)) return options.at(option).second();

	// Throw error on missing option key
	throw MissingOptionError(*this, option);
}


void Menu::addOption(const string& desc, const string& key, void (*action)())
{
	options.insert_or_assign(key, pair{desc, action});
}


void Menu::removeOption(const string& key)
{
	// Throw error on missing option key
	if (!options.contains(key)) throw MissingOptionError(*this, key);

	options.erase(key);
}


void Menu::setTitle(const string& newTitle)
{
	menu_title = newTitle;
	header_block = generateHeader();
}


void Menu::setDescription(const string& newDesc)
{
	menu_desc = newDesc;
	header_block = generateHeader();
}


void Menu::display()
{
	// Print the menu to the console
	cout << *this;

	isRunning = true;
	while (isRunning)
	{
		string input;
		cout << "\nDMS> ";
		// Get user input
		getline(cin, input);

		// Check if exit command was received
		if (input == "exit")
		{
			isRunning = false;
			break;
		}

		try
		{
			select(input);
		}
		catch (const MissingOptionError& e)
		{
			// If a command was entered, let the user know it was invalid
			if (!input.empty()) cout << "Invalid command!!" << endl;
		}
	}
}


ostream& menu::operator<<(ostream& out, const Menu& menu)
{
	out << menu.getHeaderBlock() << endl;

	auto keys = menu.options | views::keys;
	auto iter = keys.begin();

	// Display each option in the menu
	for (auto i = 0; i < keys.size() && iter != keys.end(); i++, ++iter)
	{
		out << (i + 1) << ".) " << menu.options.at(*iter).first << " [" << *iter << "]" << endl;
	}

	return out;
}
