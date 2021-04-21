#pragma once
#include <vector>
#include <string>
#include <functional>
#include <stack>

namespace menu
{
	using namespace std;
	
	class MenuController;

	class MenuNode
	{
		MenuNode* parent;
		vector<MenuNode*> child_nodes;

		string id;
	
	protected:

		MenuNode(const string& id, MenuNode* parent, MenuNode& children...);

		MenuNode(const string& id);

		MenuNode();

	public:

		MenuNode(const MenuNode& menu_node);

		const string& getId() const;

		MenuNode* getParent();

		virtual void onSelect() {}

		virtual operator string();
		
	};

	
	class MenuOption
	{
	protected:
		
		string option_text;

		function<void ()>* onSelHandler = nullptr;

	public:
		
		explicit MenuOption(const string& text) : option_text(text) {}

		MenuOption(const MenuOption& other);

		void setOnSelect(function<void()> func);
		
		const string& getText() const { return option_text; }

		virtual void onSelect();

		MenuOption& operator =(const MenuOption& other);
	};
	

	class Menu
	{
	protected:

		string menu_title;
		vector<MenuOption*> menu_options;
		
		// Optional pointer to a parent menu
		const Menu* parent_menu = nullptr;
		MenuController* controller;

	public:

		Menu() = default;

		explicit Menu(const string& title);

		Menu(MenuController& controller, const Menu& parent, const string& title);

		Menu(MenuController& controller, const string& title);

		void addOption(MenuOption& option);
		void removeOption(unsigned int index);

		const string& getTitle() const { return menu_title; }
		void setTitle(const string&);

		MenuController& getController() const;
		void setController(MenuController& new_controller);
		

	};
	

	class MenuController
	{
	private:

		stack<Menu*> menu_history;

		Menu* currentMenu;

	public:

		// Constructors
		
		MenuController();

		// Functions

		void switchMenu(Menu&);
		
	};
}

