#pragma once
#include <vector>
#include <string>
#include <functional>

// TODO: Add code for interactive menu

using namespace std;


class Option
{
	string option_text;

public:

	Option(const string& text) : option_text(text) {}

	const string& getText() { return option_text; }
};


template<typename R, typename... T>
class MenuOption : public Option // Sub-classes option so we can generalize the menu options
{
	reference_wrapper<R(T...)> action;

	static const size_t args = sizeof...(T);

public:

	MenuOption(const string& text, R (option_action)(T...)) : Option(text), action(ref(*option_action)) { }

	template<typename... Arg_T>
	R operator()(Arg_T... args) 
	{
		static const std::size_t args_count = sizeof...(Arg_T);
		
		if(args_count != this->args) throw exception("Arg Count mismatch");

		return action.get()(args...);
	}

};


class Menu
{
	typedef Option option_t;

	
	vector<option_t*> menu_options; // Should probs use smart pointers for this
	string menu_title;

	const Menu* parent_menu = nullptr;

public:
	
	Menu() = default;

	Menu(const string& title);

	Menu(const Menu& parent, const string& title);

	void addOption(option_t& option);

	void removeOption(unsigned int index);

	const string& getTitle() const { return menu_title; }

	void setTitle(const string&);

	void display();

	// This is just going to call the display function
	void operator()() { display(); }

};