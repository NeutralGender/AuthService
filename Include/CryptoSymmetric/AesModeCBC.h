#ifndef _AES_MODE_CBC
#define _AES_MODE_CBC


#include "CryptoAes.h"

#include "crypto++/aes.h"
#include "crypto++/ccm.h"
#include "crypto++/modes.h"
#include "crypto++/filters.h"

#include "crypto++/secblock.h"
#include "crypto++/hex.h"

using CryptoPP::AES;
using CryptoPP::Exception;
using CryptoPP::CBC_Mode;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

class AesModeCBC : public CryptoAes
{
private:
    const size_t& iv_length;
public:
    AesModeCBC(const size_t& key_length_,
               const size_t& iv_length_);
    virtual ~AesModeCBC() {};

    void SetIV(std::vector<byte>& iv);

    void SetKeyIVLength(std::vector<byte>& key,
                        std::vector<byte>& iv);
    
    virtual void Encrypt( const std::vector<byte>& key,
                          const std::vector<byte>& iv,
                          const std::string& plaintext,
                          std::string& encoded) override;

    virtual void Decrypt( const std::vector<byte>& key,
                          const std::vector<byte>& iv,
                          const std::string& encoded,
                          std::string& plaintext) override;

    void Decrypt( const std::vector<byte>& key,
                  const std::vector<byte>& iv,
                  const std::string& encoded,
                  std::vector< byte >& plaintext);

};

#endif