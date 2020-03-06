#include "../../Include/CryptoHash/HashSHA3_256.h"


HashSHA3::HashSHA3()
{

}

HashSHA3::~HashSHA3()
{

}

void HashSHA3::AddDataToSHA3object( const std::string& message )
{
    try
    {
        sha3.Update( (const byte*)message.data(), message.size() );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void HashSHA3::SetDigestStringSHAsize( std::string& digest )
{
    try
    {
        digest.resize( sha3.DigestSize() );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void HashSHA3::CalculateDigest( std::string& digest )
{
    try
    {
        sha3.Final( (byte*)&digest[0] );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

bool HashSHA3::Verify( const std::string& message, const std::string& digest )
{
    try
    {
        sha3.Update( (const byte*)message.data(), message.size() );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }

    try
    {
        return ( sha3.Verify( (const byte*)digest.data() ) );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    
    
}

bool HashSHA3::Verify( const std::vector<byte>& message, const std::vector<byte>& digest )
{
    try
    {
        sha3.Update( (const byte*)message.data(), message.size() );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }

    try
    {
        return ( sha3.Verify( (const byte*)digest.data() ) );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    
    
}