#pragma once
#include <cstdint>
#include <sys/socket.h>
#include "address.h"

class Socket {
public:
    typedef std::shared_ptr<Socket> SocketPtr;
    Socket();
    Socket(int sockfd) : m_sockfd(sockfd) {}
    int getSock() const;
    void bind(Address::AddressPtr address);
    void listen();
    SocketPtr accept(Address::AddressPtr address);
    void connect(Address::AddressPtr address);
    ssize_t read(SocketPtr sock, char* buff, ssize_t size);
    ssize_t write(SocketPtr sock, char* buff, ssize_t size);
private:
    int m_sockfd;
    
};
