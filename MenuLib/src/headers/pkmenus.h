#pragma once
#include <concepts>


namespace menu
{

	class IMenuApp;
	class IMenu;
	
	class IDisplayable
	{
	public:
		virtual void display() = 0;
	};

	template<typename T>
	concept RunnableAppType = std::derived_from<T, IMenuApp>;

	class IMenuApp : public IDisplayable
	{
	private:

		void run();
	
	public:

		virtual void init() {}
		
		virtual void start();

		virtual void stop() {}

		template <RunnableAppType T>
		friend void runApp();
	};
}
