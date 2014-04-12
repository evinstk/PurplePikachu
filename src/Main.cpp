#include <TEMM/Application.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		temm::Application app(60.f);
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}
