#ifndef _RSACIPHER
#define _RSACIPHER

#include "CryptoAssymetric.h"

#include "sstream"

#include "crypto++/rsa.h"
#include "crypto++/osrng.h" // AutoSeededRandomPool
#include "crypto++/integer.h"
#include "crypto++/files.h"
#include "crypto++/hex.h"
#include "crypto++/base64.h"
#include "crypto++/cryptlib.h"

#include "crypto++/pssr.h"

class RSA : public CryptoAssymetric
{
private:
    CryptoPP::RSA::PrivateKey private_key;
    CryptoPP::RSA::PublicKey public_key;
    CryptoPP::AutoSeededRandomPool rng; // pseudorandom
    CryptoPP::InvertibleRSAFunction params; // params such as e, d, n for RSA CryptoSys
    

public:
    RSA( const size_t& keysize );
    virtual ~RSA();

    virtual void Key_generation() override;

    // Load Pub/Priv Key From File/std::string
    virtual void LoadPublicKeyFromFile( const std::string& pubkey_path ) override;
    virtual void LoadPrivateKeyFromFile( const std::string& privkey_path ) override;

    virtual void LoadPublicKeyFromString( const std::string& public_key_string ) override;
    virtual void LoadPrivateKeyFromString( const std::string& private_key_string ) override;

    // Saving Pub/Priv Key To File/std::sting
    virtual void SavingPublicKeyToFile(const std::string& pubkey_string) override;
    virtual void SavingPrivateKeyToFile(const std::string& privkey_string) override;

    virtual void SavingPublicKeyToString( std::string& public_key_string ) override;
    virtual void SavingPrivateKeyToString( std::string& private_key_string ) override;

    // Encryption
    virtual void Encrypt( const std::string& plaintext, std::string& ciphertext ) override;
    
    virtual void Encrypt( const std::vector<byte>& plaintext, 
                          std::vector<byte>& ciphertext ) override;

    virtual std::string Encrypt( const std::string& plaintext ) override;

    virtual void Encrypt( const std::vector<byte>& plaintext, 
                          std::string& ciphertext ) override;

    // Decryption
    virtual void Decrypt( const std::string& ciphertext, std::string& plaintext ) override;
    virtual void Decrypt( const std::vector<byte>& ciphertext, 
                          std::vector<byte>& plaintext ) override;
    virtual std::string Decrypt( const std::string& ciphertext ) override;

    // Signing
    virtual void Sign ( const std::string& message, 
                        std::string& signature ) override;

    virtual void Sign ( const std::vector< byte >& message, 
                        std::vector< byte >& signature ) override;

    virtual std::string Sign ( const std::string& message ) override;

    virtual std::vector<byte> Sign ( const std::vector<byte>& message ) override;

    // Verification
    virtual std::vector< byte > Verify( const std::string& signature) override;
    virtual std::vector< byte > Verify( const std::vector< byte >& signature) override;
};

#endif