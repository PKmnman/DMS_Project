#include "Menu.h"


Menu::Menu(const string& title)
{
	menu_title = title;
}


Menu::Menu(const Menu& parent, const string& title) : Menu(title)
{
	parent_menu = &parent;
}


void Menu::removeOption(unsigned int index)
{
	
}


void Menu::display()
{

}

void Menu::operator()()
{
}


void Menu::addOption(Option& option)
{
	menu_options.push_back(&option);
}