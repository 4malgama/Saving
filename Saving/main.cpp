#include <exception>
#include <iostream>
#pragma message( "Lonely Amalgama wants to play." )

void _main_begin();
void _main_body();
void _main_end(int&);

int main()
{
	int retCode = 0;

	try
	{
		_main_begin();

		_main_body();

		_main_end(retCode);
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return 1;
	}

	return retCode;
}