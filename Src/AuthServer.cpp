#include "../Include/AuthServer.h"


AuthServer::AuthServer(/* args */)
{
}

AuthServer::~AuthServer()
{
}

void AuthServer::ConnectAndInitDB( DBDriver& dbdriver )
{
    dbdriver.ConnectToDB();
    dbdriver.CreateTable();
}

void AuthServer::CreateSocket( Socket& socket )
{
    socket.CreateSocket();
    socket.InitSocket();
    socket.Bind();
    socket.Listen();
}

void AuthServer::LoadServerKeysFromFiles( CryptoAssymetric& assymetic,
                                          const std::string& public_key_fpath,
                                          const std::string& private_key_fpath
                                        )
{
    assymetic.LoadPublicKeyFromFile( public_key_fpath );
    assymetic.LoadPrivateKeyFromFile( private_key_fpath );
}

void AuthServer::GeneratePermanentKey()
{
    try
    {
        AesModeCBC AES(CryptoPP::AES::DEFAULT_KEYLENGTH, CryptoPP::AES::BLOCKSIZE);
        Permanent_Key.resize( CryptoPP::AES::DEFAULT_KEYLENGTH );
        AES.GenerateKey( Permanent_Key );
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void AuthServer::GeneratePermanentIV()
{
    try
    {
        AesModeCBC AES(CryptoPP::AES::DEFAULT_KEYLENGTH, CryptoPP::AES::BLOCKSIZE);
        Permanent_IV.resize( CryptoPP::AES::DEFAULT_KEYLENGTH );
        AES.GenerateKey( Permanent_IV );
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void AuthServer::LoadPermanentAESKeyFromFile( const std::string& permanent_key_fpath )
{
    Read read( permanent_key_fpath );
    read.read_form_file( Permanent_Key );

    std::cout << Permanent_Key.data() << std::endl;
}

void AuthServer::LoadPermanentAES_IV_FromFile( const std::string& permanent_IV_fpath )
{
    Read read( permanent_IV_fpath );
    read.read_form_file( Permanent_IV );

    std::cout << Permanent_IV.data() << std::endl;
}

void AuthServer::SavePermanentAESKeyToFile( const std::string& permanent_key_fpath )
{
    Write write( permanent_key_fpath );
    write.write_to_file( Permanent_Key );
}

void AuthServer::SavePermanentAES_IV_ToFile( const std::string& permanent_IV_fpath )
{
    Write write( permanent_IV_fpath );
    write.write_to_file( Permanent_IV );
}

void AuthServer::Authenticate( int clientfd,
                               sockaddr_in client,
                               DBDriver& dbdriver,
                               CryptoAssymetric& Bob
                             )
{
    try
    {
        std::string recv_message;
        recv_message.resize(768);

// Receive Encrypted Alice Login by Bob public Key
        int n = 0;
        n = read(clientfd, &recv_message[0], 568);

        std::string Alice_login;
        Bob.Decrypt(recv_message, Alice_login);

        dbdriver.WriteLogToDB( Alice_login, 
                               "Start Authentification", 
                               inet_ntoa(client.sin_addr)
                             );

        std::cout << "Alice_login: " << Alice_login << std::endl;

        sleep(1);
// End Receive Encrypted Alice Login by Bob public Key

// Receive Alice public key in plain form and Load to RSA Alice object
        RSA Alice(3072);
        Alice.Key_generation();

        n = read(clientfd, &recv_message[0], 568);

        std::string Alice_public_key;
        Alice.LoadPublicKeyFromString(recv_message);
// End Receive Alice public key in plain form and Load to RSA Alice object

// Generate Ephemeral Key, IV, Ticket for Authentification
        AesModeCBC AES(CryptoPP::AES::DEFAULT_KEYLENGTH, CryptoPP::AES::BLOCKSIZE);
        std::vector<byte> key, iv, ticket;

        AES.SetKeyIVLength(key, iv);
        ticket.resize(16);
        AES.GenerateKey(key);
        AES.SetIV(iv);
        AES.SetIV(ticket);
    
        std::cout << "Ticket: ";
        std::cout << ticket.data();
        std::cout << std::endl;
// End Generate Ephemeral Key, IV, Ticket for Authentification

// Send Signed by private Bob key and Encrypted by Alice public key AES Ephemeral Key
        sleep(1);
        std::string Encrypted_AES_key;
        Alice.Encrypt( Bob.Sign(key) , Encrypted_AES_key );

        n = write( clientfd, Encrypted_AES_key.data(), Encrypted_AES_key.size() );
// End Send Signed by private Bob key and Encrypted by Alice public key AES Ephemeral Key

// Send Signed by private Bob key and Encrypted by Alice public key AES Ephemeral IV
        sleep(1);
        std::string Encrypted_AES_iv;
        Alice.Encrypt( Bob.Sign(iv) , Encrypted_AES_iv );

        n = write( clientfd, Encrypted_AES_iv.data(), Encrypted_AES_iv.size() );
// End Send Signed by private Bob key and Encrypted by Alice public key AES Ephemeral IV

// Send Signed by private Bob key and Encrypted by Alice public key AES Ticket
        sleep(1);
        std::string Encrypted_AES_ticket;
        Alice.Encrypt( Bob.Sign(ticket) , Encrypted_AES_ticket );

        n = write( clientfd, Encrypted_AES_ticket.data(), Encrypted_AES_ticket.size() );
// End Send Signed by private Bob key and Encrypted by Alice public key AES Ticket

// Log To DB about Ephemeral Data
        dbdriver.WriteLogToDB( Alice_login, 
                               "Generate and Send Ephemeral Data to Client", 
                               inet_ntoa(client.sin_addr)
                             );
// End Log To DB about Ephemeral Data
    
// Receive And Decrypt: Encrypted By Ephemeral AES Key Hash
        sleep(1);

        std::string recv;
        recv.resize(48);
        n = read(clientfd, &recv[0], 48);

        std::string plain;
        plain.resize(32);

        AES.Decrypt( key, iv, recv, plain );
// End Receive And Decrypt: Encrypted By Ephemeral AES Key Hash

// Calculate Hash and compare with Alice message
        HashSHA3 sha;
        std::string digest;

        sha.AddDataToSHA3object(std::string{ticket.begin(), ticket.end()}+"I am Client");
        sha.SetDigestStringSHAsize(digest);
        sha.CalculateDigest(digest);

        if( plain == digest )
// End Calculate Hash and compare with Client message
        {
    // Send New Permanent key to Alice for message from Multicast
            std::string permanent_key;

            AES.Encrypt( key, iv, 
                         std::string{ Permanent_Key.begin(), Permanent_Key.end() }, 
                         permanent_key
                       );
        
            write( clientfd, permanent_key.c_str(), permanent_key.size() );
    // End Send New Permanent key to Alice for message from Multicast

    // Send New Permanent IV to Alice for message from Multicast
            std::string permanent_iv;
            AES.Encrypt( key, iv, 
                         std::string{ Permanent_IV.begin(), Permanent_IV.end() }, 
                         permanent_iv
                       );
                
            write( clientfd, permanent_iv.data(), permanent_iv.size() );
    // End Send New Permanent IV to Alice for message from Multicast

    // Log to DB about success Authentidication protocol
            dbdriver.WriteLogToDB( Alice_login, 
                                   "Client Was Authenticated", 
                                   inet_ntoa(client.sin_addr)
                                 );
    // End Log to DB about success Authentidication protocol
    }
    else
    {
        std::cout << "Error Hash" << std::endl;
        close( clientfd );
    }
    

    }
    catch( const std::exception & e )
    {
        std::cout << e.what() << std::endl;
        close( clientfd );
    }

}


void AuthServer::AuthClient( Socket& socket, 
                             DBDriver& dbdriver, 
                             CryptoAssymetric& server
                           )
{
    try
    {
        std::cout << "WaitingAuth\n" << std::endl;
        
        socklen_t len = sizeof (socket.client );
        while(1)
        {
            int clientfd = accept( socket.socketfd, 
                                   (struct sockaddr*)&socket.client, 
                                   (socklen_t*)&len
                                 );
            
            std::thread ( [this, clientfd, &server, &dbdriver, &socket] () 
                          { 
                              this->Authenticate( clientfd,
                                                  std::ref(socket.client),
                                                  std::ref(dbdriver), 
                                                  std::ref(server) 
                                                );
                              std::cout << "---------------Plus One---------------" << std::endl;
                          }

                        ).detach();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << " : " << errno << '\n';

        dbdriver.WriteLogToDB( "ClientName", 
                                e.what() + ':' + errno, 
                                std::to_string(socket.client.sin_addr.s_addr) 
                              );
    }
    
}