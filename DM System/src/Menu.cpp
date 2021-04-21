#include "Menu.h"
#include <algorithm>
#include <functional>

menu::MenuOption::MenuOption(const MenuOption& other)
{
	this->onSelHandler = other.onSelHandler;
	this->option_text = other.option_text;
}

void menu::MenuOption::setOnSelect(function<void()> func)
{
	onSelHandler = &func;
}


void menu::MenuOption::onSelect()
{
	if(onSelHandler)
	{
		(*onSelHandler)();
	}
}

menu::MenuOption& menu::MenuOption::operator=(const MenuOption& other)
{
	if(this == &other)
	{
		return *this;
	}
	
	this->onSelHandler = other.onSelHandler;
	this->option_text = other.option_text;

	return *this;
}

menu::Menu::Menu(const string& title)
{
	this->menu_title = title;
}

menu::Menu::Menu(const Menu& parent, const string& title)
{
	this->parent_menu = parent_menu;
	this->menu_title = title;
}

void menu::Menu::addOption(MenuOption& option)
{
	this->menu_options.push_back(&option);
}

void menu::Menu::removeOption(unsigned int index)
{
	if(!menu_options.empty() && index < menu_options.size())
	{
		// Set the pointer to null
		menu_options[index] = nullptr;
		// Remove the pointer from the vector
		ranges::remove_if(menu_options, [](MenuOption* a) { return a == nullptr; });
	}
	
}

void menu::Menu::setTitle(const string& newTitle)
{
	menu_title = newTitle;
}
