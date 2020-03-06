#include <iostream>

#include "Include/AuthServer.h"

#include "Include/DBDriver/DBDriverPostgres.h"
#include "Include/Network/Socket.h"
#include "Include/CryptoAssymetric/RSA.h"

int main()
{
/*
    DBDriverPostgres postgres("Auth","postgres","postgres","postgres","127.0.0.1","5432");

    postgres.ConnectToDB();
    postgres.CreateTable();
    postgres.WriteLogToDB("test1", "Init" ,"192.1.1.2");

    Socket socket( "127.0.0.1", 8000 );
    socket.CreateSocket();
    socket.InitSocket();
    socket.Bind();
    socket.Listen();

    RSA Server(2048);
*/

    DBDriverPostgres postgres("postgres", "postgres", "postgres", "127.0.0.1", "5432");
    //Socket socket( "127.0.0.1", 8000 );
     // Receive On 192.168.56.106 address
    Socket socket( "192.168.56.106", 8000 );
    RSA Server(2048);

    AuthServer auth;
    auth.ConnectAndInitDB( postgres );
    auth.CreateSocket( socket );
    auth.LoadServerKeysFromFiles( Server, "server_pubkey.dat", "server_privkey.dat" );
    //auth.GeneratePermanentKey();
    auth.LoadPermanentAESKeyFromFile( "secretkey.dat" );
    //auth.GeneratePermanentIV();
    //auth.SavePermanentAES_IV_ToFile ( "secret_iv.dat" );
    auth.LoadPermanentAES_IV_FromFile( "secret_iv.dat" );
    auth.AuthClient( socket, postgres, Server );

}