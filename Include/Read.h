#ifndef _Read
#define _Read

#include <iostream>

#include <fstream>
#include <string>
#include <vector>

typedef unsigned char byte;

class Read
{
public:
	explicit Read( const std::string& path ) : in(path)
	{
	}
	~Read()
	{
		in.close();
	}

	void read_form_file( std::vector<byte>& permanent_key );

private:
	std::ifstream in;

};

#endif