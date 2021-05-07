#include "Menu.h"
#include "DMS.h"
#include "Partition.h"
#include <ranges>

using namespace menu;
using namespace std;

Menu::Menu(const string& title, const string& description)
{
	menu_title = title;
	menu_desc = description;
}


void menu::Menu::select(const string& option)
{
	if (options.contains(option))
	{
		auto func = options.at(option);
		// Call option function
		return func();
	}
	// Should throw an exception if the option doesn't exist
}


void Menu::addOption(const string& desc, const string& key, void (*action)())
{
	options.insert_or_assign(key, action);

	temp_options.insert_or_assign(key, pair {desc, action});
	
	option_descs.push_back(desc);
}


void Menu::removeOption(const string& key)
{
	if(options.contains(key)) options.erase(key);
}

void menu::Menu::setTitle(const string& newTitle)
{
	menu_title = newTitle;
}

void menu::Menu::display()
{
	cout << "***********************************************\n"
	<< menu_title << "\n"
	<< "***********************************************\n"
	<< menu_desc << endl << endl;
	
	auto keys = temp_options | views::keys;
	auto iter = keys.begin();
	
	for(auto i = 0; i < keys.size() && iter != keys.end(); i++, ++iter)
	{
		cout << (i + 1) << ".) " << temp_options[*iter].first << " [" << *iter << "]" << endl;
	}

	string input;
	
	isRunning = true;
	while(isRunning)
	{
		cout << "DMS> ";
		getline(cin, input);
		if(input == "exit")
		{
			isRunning = false;
			break;
		}
		if(!input.empty()) temp_options[input].second();
	}
}

