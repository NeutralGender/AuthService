#ifndef TCPSOCKET
#define TCPSOCKET

#include <iostream>
#include <exception>

#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "unistd.h"
#include "string.h"

#define BACKLOG 10

class Socket
{
private:
    int socketfd = 0;
    const std::string addr;
    const size_t port;
    struct sockaddr_in server, client;
public:
    Socket( const std::string& addr, 
            const size_t& port 
          );
    ~Socket();

    void CreateSocket();
    void InitSocket();
    void Bind();
    void Listen();
    
    friend class AuthServer;
};

#endif