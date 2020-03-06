#ifndef _HASH_ABSTRACT
#define _HASH_ABSTRACT

#include <iostream>

#include "crypto++/cryptlib.h"
#include "crypto++/filters.h"

class HashAbstract
{
public:
    HashAbstract();
    ~HashAbstract();

    virtual void AddDataToSHA3object( const std::string& message ) = 0; // Add Data  
    virtual void SetDigestStringSHAsize( std::string& digest ) = 0;
    virtual void CalculateDigest( std::string& digest ) = 0;
    virtual bool Verify( const std::string& message, const std::string& digest ) = 0;

    virtual bool Verify( const std::vector<byte>& message, 
                         const std::vector<byte>& digest ) = 0;

};

#endif