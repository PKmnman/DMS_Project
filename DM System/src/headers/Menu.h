#ifndef MENU_H
#define MENU_H

#include <map>
#include <string>
#include <functional>
#include <exception>
#include <stdexcept>

namespace menu
{
	using namespace std;

	
	
	class Menu
	{
	protected:

		// The title and description of the menu
		string menu_title, menu_desc;
		
		string header_block;

		// Flag to track whether the menu is active
		bool isRunning;
		
		// Maps command strings to functions
		map<string, pair<string, void (*)()>> options;
		
		// Optional pointer to a parent menu
		const Menu* parent_menu = nullptr;

		string generateHeader() const;

	public:

		Menu() = default;

		explicit Menu(const string& title, const string& description);

		// Basically runs the menu, displaying options and grabbing input
		void display();

		// Tries to call the function associated with the given option key.
		void select(const string& option);
		
		// Adds an option to the menu
		void addOption(const string& desc, const string& key, void(*action)());

		// Removes an option from the menu
		void removeOption(const string& key);

		const string& getHeaderBlock() const { return header_block; }
		
		const string& getTitle() const { return menu_title; }
		void setTitle(const string&);

		const string& getDescription() const { return menu_desc; }
		void setDescription(const string&);

		friend ostream& operator<<(ostream& out, const Menu& menu);

	};
	
	ostream& operator<<(ostream& out, const Menu& menu);
	
	class MissingOptionError : public runtime_error
	{
		const Menu& source_menu;
		const string option_name;

		static string format_msg(const string& menu, const string& option);

	public:

		explicit MissingOptionError(const Menu& menu, const string& option)
			: runtime_error(format_msg(menu.getTitle(), option)), source_menu(menu), option_name(option)  {}

		
		const Menu& getSource() const { return source_menu; }

		const string& getOption() const { return option_name; }
		
	};

}

#endif