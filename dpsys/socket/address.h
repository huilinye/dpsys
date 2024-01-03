#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdint>
#include <memory>
#include <cstring>

class Address {
    
public:
    typedef std::shared_ptr<Address> AddressPtr;
    Address();
    Address( const char* address, uint32_t port);
    sockaddr* getAddress();
private :
    sockaddr_in m_sockaddr;
};

