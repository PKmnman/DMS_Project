#include "Menu.h"
#include <algorithm>
#include <functional>

using namespace menu;
using namespace std;

Menu::Menu(const string& title)
{
	this->menu_title = title;
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


void Menu::addOption(const string& key, void (*action)())
{
	options.insert_or_assign(key, action);
}


void Menu::removeOption(const string& key)
{
	if(options.contains(key)) options.erase(key);
}

void menu::Menu::setTitle(const string& newTitle)
{
	menu_title = newTitle;
}