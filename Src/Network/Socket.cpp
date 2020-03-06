#include "../../Include/Network/Socket.h"

Socket::Socket( const std::string& addr_, 
                const size_t& port_ 
              ):addr(addr_), port(port_)
{
}

Socket::~Socket()
{
}

void Socket::CreateSocket()
{
    try
    {
        if( ( socketfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
            throw std::runtime_error("Cannot create socket! ");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << errno << '\n';
    }
    
}

void Socket::InitSocket()
{
    try
    {
        bzero( &server, sizeof(server) );
        server.sin_family = AF_INET;
        server.sin_port = htons( port );
        server.sin_addr.s_addr = inet_addr( addr.c_str() );
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void Socket::Bind()
{
    try
    {
        int check = 0;
        if( ( check = bind( socketfd, (struct sockaddr*)&server, sizeof(server) ) ) < 0 )
            throw std::runtime_error("Cannot Bind socket! ");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << errno << '\n';
    }
    
}

void Socket::Listen()
{
    try
    {
        int check = 0;
        if( ( check = listen( socketfd, BACKLOG ) ) < 0 )
            throw std::runtime_error("Cannot Listen socket! ");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << errno << '\n';
    }
    
}
