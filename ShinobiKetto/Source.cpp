
#include "Application.h"

#include <stdexcept>
#include <iostream>
int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\n\nEXCEPTION:" << e.what() << std::endl;
	}
}