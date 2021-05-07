#ifndef MENU_H
#define MENU_H

#include <map>
#include <string>
#include <functional>

namespace menu
{
	using namespace std;

	class Menu
	{
	protected:

		string menu_title;
		string menu_desc;

		// Maps command strings to functions
		map<string, void (*)()> options;
		// Contains the strings shown to the user for each option
		vector<string> option_descs;

		bool isRunning;

		map<string, pair<string, void (*)()>> temp_options;
		
		// Optional pointer to a parent menu
		const Menu* parent_menu = nullptr;

	public:

		Menu() = default;

		explicit Menu(const string& title, const string& description);

		void select(const string& option);

		// Adds an option to the menu
		void addOption(const string& desc, const string& key, void(*action)());

		// Removes an option from the menu
		void removeOption(const string& key);

		const string& getTitle() const { return menu_title; }
		void setTitle(const string&);

		// Basically runs the menu, displaying options and grabbing input
		void display();
	};

}

#endif