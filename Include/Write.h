#ifndef _Write
#define _Write

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

typedef unsigned char byte;

class Write
{
public:
	explicit Write( const std::string &path ) : wr ( path, std::ios_base::binary | 
														  std::ios_base::trunc 
												   ) 
	{

	}
	~Write();

	void write_to_file( const std::vector<byte>& permanent_key );

private:
	std::ofstream wr;
};

#endif