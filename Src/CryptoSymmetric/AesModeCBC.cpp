#include "../../Include/CryptoSymmetric/AesModeCBC.h"

AesModeCBC::AesModeCBC(const size_t& key_length_,
                       const size_t& iv_length_)
                     : CryptoAes(key_length_),
                       iv_length(iv_length_)
{
}

void AesModeCBC::SetIV( std::vector<byte>& iv )
{
    try
    {
        prng.GenerateBlock( iv.data(), iv_length);
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void AesModeCBC::SetKeyIVLength(std::vector<byte>& key,
                                std::vector<byte> &iv)
{
    try
    {
        key.resize(this->key_length);
        iv.resize(this->iv_length);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void AesModeCBC::Encrypt( const std::vector<byte>& key,
                          const std::vector<byte>& iv,
                          const std::string& plaintext,
                          std::string& encoded)
{
    try
    {
        CBC_Mode<AES>::Encryption e;
        e.SetKeyWithIV( key.data(), key.size(), iv.data() );

        
        StringSource ss( plaintext,
                         true,
                         new StreamTransformationFilter // adding padding as required
                         (                             //  CBC must be padded
                             e,
                             new CryptoPP::StringSink(encoded)
                         )
                       );
        
/*
       StringSource ss(plaintext,
                        true,
                        new StreamTransformationFilter // adding padding as required
                        (                             //  CBC must be padded
                            e,
                            new CryptoPP::HexEncoder
                            (
                                new CryptoPP::StringSink(encoded)
                            )
                        )
                      );
*/

    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void AesModeCBC::Decrypt( const std::vector<byte>& key,
                          const std::vector<byte>& iv,
                          const std::string& encoded,
                          std::string& plaintext)
{
    try
    {
        bzero(&plaintext, sizeof(plaintext));

        CBC_Mode<AES>::Decryption d;
        d.SetKeyWithIV( key.data(), key.size(), iv.data() );

        
        StringSource ss(encoded,
                        true,
                        new StreamTransformationFilter // removing padding as required
                        (                             //  CBC must be padded
                            d,
                            new CryptoPP::StringSink(plaintext)
                        )
                        );
        
/*
       StringSource ss(encoded,
                        true,
                        new CryptoPP::HexDecoder
                        (
                            new StreamTransformationFilter // removing padding as required
                            (                             //  CBC must be padded
                                d,
                                new CryptoPP::StringSink(plaintext)
                            )
                        )
                        );
*/    
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}

void AesModeCBC::Decrypt( const std::vector<byte>& key,
                          const std::vector<byte>& iv,
                          const std::string& encoded,
                          std::vector< byte >& plaintext)
{
    try
    {
        plaintext.resize(16);

        CBC_Mode<AES>::Decryption d;
        d.SetKeyWithIV( key.data(), key.size(), iv.data() );

/*
        CryptoPP::ArraySource ss(encoded,
                                 true,
                                 new CryptoPP::HexDecoder
                                 (
                                    new StreamTransformationFilter // removing padding as required
                                    (                             //  CBC must be padded
                                        d,
                                        new CryptoPP::ArraySink(plaintext.data(),
                                                                plaintext.size())
                                    )
                                 )
                                );
*/

        CryptoPP::ArraySource ss(encoded,
                                 true,
                                 new StreamTransformationFilter // removing padding as required
                                 (                             //  CBC must be padded
                                    d,
                                    new CryptoPP::ArraySink(plaintext.data(),
                                                            plaintext.size())
                                 )
                                );   
            
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}