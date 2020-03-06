#ifndef _SHA3
#define _SHA3

#include "HashAbstract.h"

#include "crypto++/sha3.h"

class HashSHA3 : public HashAbstract
{
private:
    CryptoPP::SHA3_256 sha3;
public:
    HashSHA3();
    virtual ~HashSHA3();

    virtual void AddDataToSHA3object( const std::string& message ) override; // Add Data  
    virtual void SetDigestStringSHAsize( std::string& digest ) override;
    virtual void CalculateDigest( std::string& digest ) override;
    virtual bool Verify( const std::string& message, const std::string& digest ) override;

    virtual bool Verify( const std::vector<byte>& message, 
                         const std::vector<byte>& digest ) override;
};

#endif