#include "../Include/Write.h"


Write::~Write()
{
	wr.close();
}

void Write::write_to_file( const std::vector<byte>& permanent_key )
{
	try
	{
		if (!wr.is_open())
			throw std::runtime_error("Cannot open write file!");

		for( auto &n : permanent_key )
		{
			wr << n;
		}
			
	}
	catch (const std::runtime_error & r)
	{
		std::cout << r.what() << std::endl;
	}
}
