#ifndef _CRYPTO_AES
#define _CRYPTO_AES

#include <iostream>
#include "CryptoSymmetric.h"

#include "crypto++/aes.h"
#include "crypto++/osrng.h"

class CryptoAes : public CryptoSymmetric
{
protected:
    CryptoPP::AutoSeededRandomPool prng;
public:
    CryptoAes( const size_t& key_length_ );
    virtual ~CryptoAes();

    virtual void GenerateKey(std::vector<byte>& key) final;
};

#endif