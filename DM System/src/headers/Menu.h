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

		map<string, void (*)()> options;
		vector<string> option_descs;

		bool isRunning;
		
		// Optional pointer to a parent menu
		const Menu* parent_menu = nullptr;

	public:

		Menu() = default;

		explicit Menu(const string& title, const string& description);

		void select(const string& option);

		void addOption(const string& desc, const string& key, void(*action)());
		void removeOption(const string& key);

		const string& getTitle() const { return menu_title; }
		void setTitle(const string&);

		void display();
	};

}

#endif