#pragma once
#include <vector>
#include <string>
#include <functional>
#include <concepts>
#include <map>

namespace menu
{
	using namespace std;
	
	class MenuOption
	{
		string option_text;

		function<void ()>* onSelHandler = nullptr;

	public:
		
		explicit MenuOption(const string& text) : option_text(text) {}

		MenuOption(const MenuOption& other);

		void setOnSelect(function<void()> func);
		
		const string& getText() const { return option_text; }

		void onSelect();

		MenuOption& operator =(const MenuOption& other);
	};
	

	class Menu
	{
	protected:

		vector<MenuOption*> menu_options; // Should probs use smart pointers for this
		string menu_title;

		// Optional pointer to a parent menu
		const Menu* parent_menu = nullptr;

		const unsigned long menu_id = 0;

	public:

		Menu() = default;

		explicit Menu(const string& title);

		Menu(const Menu& parent, const string& title);

		void addOption(MenuOption& option);

		void removeOption(unsigned int index);

		const string& getTitle() const { return menu_title; }

		void setTitle(const string&);

		// This function simply prints out the menu to the console
		void display();

	};
}

