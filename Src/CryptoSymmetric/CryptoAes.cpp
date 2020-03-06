#include "../../Include/CryptoSymmetric/CryptoAes.h"

CryptoAes::CryptoAes( const size_t& key_length_ ) 
                    : CryptoSymmetric( key_length_ )
{
}

CryptoAes::~CryptoAes()
{
    
}

void CryptoAes::GenerateKey(std::vector<byte>& key)
{
    try
    {
        prng.GenerateBlock( key.data(), key_length );
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
