#ifndef _CRYPTOASSYM
#define _CRYPTOASSYM

typedef unsigned char byte;

#include <iostream>
#include <vector>
#include <string>


class CryptoAssymetric
{
protected:
    const size_t& keysize;    
public:
    CryptoAssymetric( const size_t& keysize_ );
    ~CryptoAssymetric();

    virtual void Key_generation() = 0;

    // Load Pub/Priv Key From File/std::string
    virtual void LoadPublicKeyFromFile( const std::string& pubkey_path ) = 0;
    virtual void LoadPrivateKeyFromFile( const std::string& privkey_path ) = 0;

    virtual void LoadPublicKeyFromString( const std::string& public_key_string ) = 0;
    virtual void LoadPrivateKeyFromString( const std::string& private_key_string ) = 0;

    // Saving Pub/Priv Key To File/std::sting
    virtual void SavingPublicKeyToFile(const std::string& pubkey_string) = 0;
    virtual void SavingPrivateKeyToFile(const std::string& privkey_string) = 0;

    virtual void SavingPublicKeyToString( std::string& public_key_string ) = 0;
    virtual void SavingPrivateKeyToString( std::string& private_key_string ) = 0;

    // Encryption
    virtual void Encrypt( const std::string& plaintext, std::string& ciphertext ) = 0;

    virtual void Encrypt( const std::vector<byte>& plaintext, 
                          std::vector<byte>& ciphertext ) = 0;

    virtual std::string Encrypt( const std::string& plaintext ) = 0;

    virtual void Encrypt( const std::vector<byte>& plaintext, 
                          std::string& ciphertext ) = 0;

    // Decryption
    virtual void Decrypt( const std::string& ciphertext, std::string& plaintext ) = 0;

    virtual void Decrypt( const std::vector<byte>& ciphertext, 
                          std::vector<byte>& plaintext ) = 0;

    virtual std::string Decrypt( const std::string& ciphertext ) = 0;

    // Signing
    virtual void Sign ( const std::string& message, 
                        std::string& signature ) = 0;
                        
    virtual void Sign ( const std::vector< byte >& message, 
                        std::vector< byte >& signature ) = 0;

    virtual std::string Sign ( const std::string& message ) = 0;

    virtual std::vector<byte> Sign ( const std::vector<byte>& message ) = 0;

    // Verification
    virtual std::vector< byte > Verify( const std::string& signature) = 0;

    virtual std::vector< byte > Verify( const std::vector< byte >& signature) = 0;
};

#endif