#ifndef AUTHSERVER
#define AUTHSERVER

#include <string>
#include <thread>
#include <vector>

#include "Read.h"
#include "Write.h"
#include "Network/Socket.h"
#include "DBDriver/DBDriver.h"

#include "CryptoAssymetric/RSA.h"
#include "CryptoHash/HashSHA3_256.h"
#include "CryptoSymmetric/AesModeCBC.h"

class AuthServer
{
private:
    std::vector< byte > Permanent_Key;
    std::vector< byte > Permanent_IV;
public:
    AuthServer();
    ~AuthServer();

    void ConnectAndInitDB( DBDriver& dbdriver ); // Connect to DB and create AuthTable
    void WriteLogToDB( DBDriver& dbdriver );

    void CreateSocket( Socket& socket );

    void LoadServerKeysFromFiles( CryptoAssymetric& assymetic,
                                  const std::string& public_key_fpath,
                                  const std::string& private_key_fpath
                                );
  
    void GeneratePermanentKey();

    void GeneratePermanentIV();

    void LoadPermanentAESKeyFromFile( const std::string& permanent_key_fpath );

    void LoadPermanentAES_IV_FromFile( const std::string& permanent_IV_fpath );

    void SavePermanentAESKeyToFile( const std::string& permanent_key_fpath );

    void SavePermanentAES_IV_ToFile( const std::string& permanent_IV_fpath );

    void Authenticate( int clientfd,
                       sockaddr_in client,
                       DBDriver& dbdriver,
                       CryptoAssymetric& Bob
                     );

    void AuthClient( Socket& socket, 
                     DBDriver& dbdriver, 
                     CryptoAssymetric& server
                   );
};

#endif
