#include "../Include/Read.h"


void Read::read_form_file( std::vector<byte>& permanent_key )
{
	try
	{
		if (!in.is_open())
			throw std::runtime_error("Error, cannot open file!\n");

		char ch;
		while( in >> ch )
		{
			permanent_key.push_back(ch);
		}
		
	}
	catch (const std::runtime_error &r)
	{
		std::cout << r.what() << std::endl;
	}
}